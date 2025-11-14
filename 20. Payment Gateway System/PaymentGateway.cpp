# include <iostream>
# include <vector>
using namespace std;

struct PaymentRequest {
    string receiver;
    string sender;
    double amount;
    string currency;

    PaymentRequest(string receiver, string sender, double amount, string currency) {
        this->sender = sender;
        this->receiver = receiver;
        this->amount = amount;
        this->currency = currency;
    }
};


class BankingSystem {
public:
    virtual bool processPayment(double amount) = 0;
    virtual ~BankingSystem() {};
};

class PaytmBankingSystem : public BankingSystem {
public:
    bool processPayment(double amount) override {
        int r = rand() % 100;
        return r < 20;
    }
};

class RayzorpayBankingSystem : public BankingSystem {
public:
    bool processPayment(double amount) override {
        int r = rand() % 100;
        return r < 90;
    }
};

class PaymentGateway {
protected:
    BankingSystem* bankingSystem;
public:
    PaymentGateway() {
        bankingSystem = nullptr;
    }

    virtual bool validatePayment(PaymentRequest* request) = 0;
    virtual bool initiatePayment(PaymentRequest* request) = 0;
    virtual bool confirmPayment(PaymentRequest* request) = 0;


    virtual bool processPayment(PaymentRequest* request) {
         if (!validatePayment(request)) {
            cout << "[PaymentGateway] Validation failed for " << request->sender << ".\n";
            return false;
        }
        if (!initiatePayment(request)) {
            cout << "[PaymentGateway] Initiation failed for " << request->sender << ".\n";
            return false;
        }
        if (!confirmPayment(request)) {
            cout << "[PaymentGateway] Confirmation failed for " << request->sender << ".\n";
            return false;
        }
        return true;
    }
};

class PaytmGateway : public PaymentGateway{
public:
    PaytmGateway() {
        bankingSystem = new PaytmBankingSystem();
    }

    bool validatePayment(PaymentRequest* request) override {
        cout << "[Paytm] Validating payment for " << request->sender << ".\n";

        if (request->amount <= 0 || request->currency != "INR") {
            return false;
        }
        return true;
    }
    bool initiatePayment(PaymentRequest* request) override {
        cout << "[Paytm] Initiating payment of " << request->amount  << " " << request->currency << " for " << request->sender << ".\n";

        return bankingSystem->processPayment(request->amount);
    }
    bool confirmPayment(PaymentRequest* request) override {
        cout << "[Paytm] Confirming payment for " << request->sender << ".\n";

        return true;
    }
};

class RazorpayGateway : public PaymentGateway {
public:
    RazorpayGateway() {
        bankingSystem = new RayzorpayBankingSystem();
    }
    bool validatePayment(PaymentRequest* request) override {
        cout << "[Razorpay] Validating payment for " << request->sender << ".\n";

        if (request->amount <= 0) {
            return false;
        }
        return true;
    }
    bool initiatePayment(PaymentRequest* request) override {
        cout << "[Razorpay] Initiating payment of " << request->amount 
                  << " " << request->currency << " for " << request->sender << ".\n";

        return bankingSystem->processPayment(request->amount);
       
    }
    bool confirmPayment(PaymentRequest* request) override {
        cout << "[Razorpay] Confirming payment for " << request->sender << ".\n";

        return true;
    }
};

class PaymentGatewayProxy : public PaymentGateway {
private:
    PaymentGateway* realGateway;
    int retries;
public:
    PaymentGatewayProxy(PaymentGateway* gateway, int maxRetries) {
        realGateway = gateway;
        retries = maxRetries;
    }
    bool processPayment(PaymentRequest* request) override {
        bool result = false;
        for (int attempt = 0; attempt < retries; ++attempt) {
            if (attempt > 0) {
                cout << "[Proxy] Retrying payment (attempt " << (attempt+1) << ") for " << request->sender << ".\n";
            }
            result = realGateway->processPayment(request);
            if (result) break;
        }
        if (!result) {
            cout << "[Proxy] Payment failed after " << (retries) << " attempts for " << request->sender << ".\n";
        }
        return result;
    }
    bool validatePayment(PaymentRequest* request) override {
        return realGateway->validatePayment(request);
    }
    bool initiatePayment(PaymentRequest* request) override {
        return realGateway->initiatePayment(request);
    }
    bool confirmPayment(PaymentRequest* request) override {
        return realGateway->confirmPayment(request);
    }
};

// ----------------------------
// Gateway Factory for creating gateway (Singleton)
// ----------------------------
enum class GatewayType { 
    PAYTM, 
    RAZORPAY
};

class GatewayFactory {
private:
    static GatewayFactory instance;
    GatewayFactory() {}
    GatewayFactory(const GatewayFactory&) = delete;
    GatewayFactory& operator=(const GatewayFactory&) = delete;
    
public:
    static GatewayFactory& getInstance() {
        return instance;
    }
    PaymentGateway* getGateway(GatewayType type) {
        if (type == GatewayType::PAYTM) {
            PaymentGateway* paymentGateway = new PaytmGateway();
            return new PaymentGatewayProxy(paymentGateway, 3);
        } else {
            PaymentGateway* paymentGateway = new RazorpayGateway();
            return new PaymentGatewayProxy(paymentGateway, 1);
        }
    }
};

GatewayFactory GatewayFactory::instance;

// ----------------------------
// Unified API service (Singleton)
// ----------------------------
class PaymentService {
private:
    static PaymentService instance;
    PaymentGateway* gateway;

    PaymentService() { 
        gateway = nullptr; 
    }
    ~PaymentService() { 
        delete gateway; 
    }

    // Private constructor and delete copy/assignment to ensure no one can clone or reassign your singleton.
    PaymentService(const PaymentService&) = delete;
    PaymentService& operator=(const PaymentService&) = delete;

public:
    static PaymentService& getInstance() {
        return instance;
    }
    void setGateway(PaymentGateway* g) {
        if (gateway) delete gateway;
        gateway = g;
    }
    bool processPayment(PaymentRequest* request) {
        if (!gateway) {
            cout << "[PaymentService] No payment gateway selected.\n";
            return false;
        }
        return gateway->processPayment(request);
    }
};

PaymentService PaymentService::instance;

// ----------------------------
// Controller class for all client requests (Singleton)
// ----------------------------
class PaymentController {
private:
    static PaymentController instance;
    PaymentController() {}
    PaymentController(const PaymentController&) = delete;
    PaymentController& operator=(const PaymentController&) = delete;
public:
    static PaymentController& getInstance() {
        return instance;
    }
    bool handlePayment(GatewayType type, PaymentRequest* req) {
        PaymentGateway* paymentGateway = GatewayFactory::getInstance().getGateway(type);
        PaymentService::getInstance().setGateway(paymentGateway);
        return PaymentService::getInstance().processPayment(req);
    }
};

PaymentController PaymentController::instance;


int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    PaymentRequest* req1 = new PaymentRequest("Garima", "Gautam", 1000.0, "INR");

    cout << "Processing via Paytm\n";
    cout << "------------------------------\n";
    bool res1 = PaymentController::getInstance().handlePayment(GatewayType::PAYTM, req1);
    cout << "Result: " << (res1 ? "SUCCESS" : "FAIL") << "\n";
    cout << "------------------------------\n\n";

    PaymentRequest* req2 = new PaymentRequest("Gautam", "Garima", 500.0, "USD");

    cout << "Processing via Razorpay\n";
    cout << "------------------------------\n";
    bool res2 = PaymentController::getInstance().handlePayment(GatewayType::RAZORPAY, req2);
    cout << "Result: " << (res2 ? "SUCCESS" : "FAIL") << "\n";
    cout << "------------------------------\n";

    return 0;
}
