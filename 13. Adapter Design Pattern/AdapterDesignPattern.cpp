# include <iostream>
using namespace std;

class IReport{
public:
    virtual string getJSON(const string& data) = 0;
    virtual ~IReport() {};
};

class XMLDataProvider {
public:
    string getXML(const string& data) {
        size_t sep = data.find(':');
        string name = data.substr(0, sep);
        string id   = data.substr(sep + 1);
        // Build an XML representation
        return "<user>"
               "<name>" + name + "</name>"
               "<id>"   + id   + "</id>"
               "</user>";
    }
};

class XMLDataProviderAdapter : public IReport { //is-a
private:
    XMLDataProvider* xmlprovider; // has-a
public:
    XMLDataProviderAdapter(XMLDataProvider* xmlprovider) {
        this->xmlprovider = xmlprovider;
    }
    string getJSON(const string& data) {
        string xml = xmlprovider->getXML(data);

        // 2. Naïvely parse out <name> and <id> values
        size_t startName = xml.find("<name>") + 6;
        size_t endName   = xml.find("</name>");
        string name      = xml.substr(startName, endName - startName);

        size_t startId = xml.find("<id>") + 4;
        size_t endId   = xml.find("</id>");
        string id      = xml.substr(startId, endId - startId);

        // 3. Build and return JSON
        return "{\"name\":\"" + name + "\", \"id\":" + id + "}";
    }
};

class Client {
public:
    void getReport(IReport* report, string rawData) {
        cout << "Processed JSON: "
        << report->getJSON(rawData)
        << endl;
    }
};
int main() {

    XMLDataProvider* xmlprovider = new XMLDataProvider();

    IReport* adapter = new XMLDataProviderAdapter(xmlprovider);

    string rawData = "Gaima: 27";

    Client* c = new Client();

    c->getReport(adapter,rawData);

    delete adapter;
    delete xmlprovider;
   
}