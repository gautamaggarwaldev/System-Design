# include <iostream>
# include <vector>
# include <fstream>

using namespace std;
class DocumentEditor {
private:
    vector<string> documentElements;
    string renderedDocument;
public:
    void addText(string text) {
        documentElements.push_back(text);
    }

    void addImage(string path) {
        documentElements.push_back(path);
    }

    string renderDocument() {
        if(renderedDocument.empty()) {
            string result;
            for (auto element : documentElements) {
                if (element.size() > 4 && (element.substr(element.size() - 4) == ".jpg" ||
                 element.substr(element.size() - 4) == ".png")) {
                    result += "[Image: " + element + "]" + "\n";
                } else {
                    result += element + "\n";
                }
            }
            renderedDocument = result;
        }
        return renderedDocument;
    }

    void saveToFile() {
        ofstream file("file.txt");
        if(file.is_open()) {
            file << renderDocument();
            file.close();
            cout << "Document save into the file...";
        }
        else {
            cout << "Error in opening the file...";
        }
    }
};

int main() {
    DocumentEditor de;

    de.addText("Hello World");
    de.addImage("C:/Users/gg/images/my.jpg");

    cout << de.renderDocument() << endl;

    de.saveToFile();
}


