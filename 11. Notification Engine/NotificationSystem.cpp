# include <iostream>
# include <vector>
# include <algorithm>
# include <ctime>
# include <chrono>
# include <sstream>
# include <iomanip>
using namespace std;

/*============================
    Notification & Decorators
=============================*/

class INotification {
public:
    virtual string getContent() = 0;
    virtual ~INotification() {};
};

class SimpleNotification : public INotification {
private:
    string text;
public:
    SimpleNotification(const string& msg) {
        this->text = msg;
    }

    string getContent() override {
        return text;
    }
};

class INotificationDecorator : public INotification {
protected: 
    INotification* notification;
public:
    INotificationDecorator(INotification* n){
        this->notification = n;
    }

    virtual ~INotificationDecorator() {
        delete notification;
    }
};


class TimeStampNotificaion : public INotificationDecorator {
public:
    TimeStampNotificaion(INotification* n) : INotificationDecorator(n) {}

    string getContent() override {
        // Get current system time
        auto now = chrono::system_clock::now();
        time_t currentTime = chrono::system_clock::to_time_t(now);
        tm localTime{};
        localtime_s(&localTime, &currentTime);

        ostringstream oss;
        oss << "[" << put_time(&localTime, "%Y-%m-%d %H:%M:%S") << "] ";

        return oss.str() + notification->getContent();
    }
};

class SignatureNotification : public INotificationDecorator {
private: 
    string signature;
public:
    SignatureNotification(INotification* n, const string& sign) : INotificationDecorator(n) {
        this->signature = sign;
    }
    
    string getContent() override {
        return notification->getContent() + "\n-- " + signature + "\n\n";
    }
};

/*============================
  Observer Pattern Components
=============================*/

class IObserver {
public:
    virtual void update() = 0;
    virtual ~IObserver() {};
};

class IObservable {
public:
    virtual void addObserver(IObserver* obsever) = 0;
    virtual void removeObserver(IObserver* obsever) = 0;
    virtual void notifyObserver() = 0;
};

class NotificationObservable : public IObservable {
private:
    vector<IObserver*>observers;
    INotification* currentNotification;
public:
    NotificationObservable() { 
        currentNotification = nullptr; 
    }

    void addObserver(IObserver* observer) override {
        observers.push_back(observer);
    }

    void removeObserver(IObserver* observer) override {
        observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notifyObserver() override {
        for(auto observer : observers) {
            observer->update();
        }
    }

    INotification* getNotification() {
        return currentNotification;
    }

    void setNotification(INotification* notification) {
        if (currentNotification != nullptr) {
            delete currentNotification;
        }
        currentNotification = notification;
        notifyObserver();
    }

    string getNotificationContent() {
        return currentNotification->getContent();
    }

    ~NotificationObservable() {
        if (currentNotification != NULL) {
            delete currentNotification;
        }
    }
};

// Concrete Observer 1
class Logger : public IObserver {
private:
    NotificationObservable* notificationObservable;
public:
    Logger(NotificationObservable* notificationObservable) {
        this->notificationObservable = notificationObservable;
    }

    void update() {
        cout << "Logging New Notification : \n" << notificationObservable->getNotificationContent();
    }
};

/*============================
  Strategy Pattern Components (Concrete Observer 2)
=============================*/

class INotificationStrategy {
public:
    virtual void sendNotification(string content) = 0;
    virtual ~INotificationStrategy() {};
};

class EmailStrategy : public INotificationStrategy {
private:
    string email;
public:
    EmailStrategy(const string& email) {
        this->email = email;
    }

    void sendNotification(string content) {
        cout << "Sending email Notification to: " << email << "\n" << content;
    }
};

class SMSStrategy : public INotificationStrategy {
private: 
    string mobile;
public:
    SMSStrategy(const string& mobile) {
        this->mobile = mobile;
    } 

    void sendNotification(string content) {
        cout << "Sending SMS Notification to: " << mobile << "\n" << content;
    }
};

class POPUPStrategy : public INotificationStrategy {
public:
    void sendNotification(string content) override {
        cout << "Sending Popup Notification: \n" << content;
    }
};

class NotificationEngine : public IObserver {
private:
    NotificationObservable* notificationObservable;
    vector<INotificationStrategy*> notificationStrategies;
public:
    NotificationEngine(NotificationObservable* notificationObservable) {
        this->notificationObservable = notificationObservable;
    }

    void addNotificationStrategy(INotificationStrategy* ns) {
        notificationStrategies.push_back(ns);
    }

    void update() {
        string notificationContent = notificationObservable->getNotificationContent();
        for(auto ns : notificationStrategies) {
            ns->sendNotification(notificationContent);
        }
    }
};

/*============================
    NotificationService
=============================*/

// The NotificationService manages notifications. It keeps track of notifications. 
// Any client code will interact with this service.

class NotificationService {
private:
    vector<INotification*> notifications;
    NotificationObservable* observable;
    static NotificationService* instance;

    NotificationService() {
        observable = new NotificationObservable();
    };

public:
    static NotificationService* getInstance() {
        if(instance==nullptr) {
            instance = new NotificationService();
        }
        return instance;
    }

    NotificationObservable* getObservable() {
        return observable;
    }

    void sendNotification(INotification* notification) {
        notifications.push_back(notification); //history
        observable->setNotification(notification);
    }

    ~NotificationService() {
        delete observable;
    }
};

NotificationService* NotificationService::instance = nullptr;

int main() {
    // Create NotificationService.
    NotificationService* notificationService = NotificationService::getInstance();

    // Get Observable
    NotificationObservable* notificationObservable = notificationService->getObservable();
   
    // Create Logger Observer
    Logger* logger = new Logger(notificationObservable);

    // Create NotificationEngine observers.
    NotificationEngine* notificationEngine = new NotificationEngine(notificationObservable);

    notificationEngine->addNotificationStrategy(new EmailStrategy("random.person@gmail.com"));
    notificationEngine->addNotificationStrategy(new SMSStrategy("+91 9876543210"));
    notificationEngine->addNotificationStrategy(new POPUPStrategy());

    // Attach these observers.
    notificationObservable->addObserver(logger);
    notificationObservable->addObserver(notificationEngine);

    // Create a notification with decorators.
    INotification* notification = new SimpleNotification("Your order has been shipped!");
    notification = new TimeStampNotificaion(notification);
    notification = new SignatureNotification(notification, "Customer Care");
    
    notificationService->sendNotification(notification);

    delete logger;
    delete notificationEngine;



}