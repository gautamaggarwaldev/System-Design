
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

// Abstract base class for all document elements
class DocumentElement
{
public:
    // Render the element to a string representation
    virtual string render() = 0;
};

// Concrete element that holds plain text
class TextElement : public DocumentElement
{
private:
    string text;

public:
    TextElement(string text)
    {
        this->text = text;
    }

    string render() override
    {
        return text;
    }
};

// Concrete element that represents an image (rendered as a placeholder string)
class ImageElement : public DocumentElement
{
private:
    string path;

public:
    ImageElement(string path)
    {
        this->path = path;
    }

    string render() override
    {
        return "[Image: " + path + "]";
    }
};

// Element that represents a newline in the document
class NewLineElement : public DocumentElement
{
public:
    string render() override
    {
        return "\n";
    }
};

// Element that represents a tab character in the document
class TabElement : public DocumentElement
{
public:
    string render() override
    {
        return "\t";
    }
};

// Document is a collection of DocumentElement pointers
class Document
{
private:
    vector<DocumentElement *> docElements;

public:
    // Add an element to the document
    void addElement(DocumentElement *element)
    {
        docElements.push_back(element);
    }

    // Render the whole document by concatenating each element's rendered string
    string render()
    {
        string result;
        for (auto ele : docElements)
        {
            result += ele->render();
        }
        return result;
    }
};

// Persistence interface for saving document data
class PersistenceDB
{
public:
    virtual void save(string data) = 0;
};

// File-based storage implementation of PersistenceDB
class FileStorage : public PersistenceDB
{
public:
    void save(string data) override
    {
        ofstream outFile("file.txt");
        if (outFile)
        {
            outFile << data;
            outFile.close();
            cout << "Document saved to file.txt" << endl;
        }
        else
        {
            cout << "Error: Unable to open file for writing." << endl;
        }
    }
};

// Simulated database storage implementation
class DataBaseStorage : public PersistenceDB
{
public:
    void save(string data) override
    {
        cout << data << " saved on database successfully...";
    }
};

// DocumentEditor composes a Document and a PersistenceDB to edit and save documents
class DocumentEditor
{
private:
    Document *document;      // pointer to the document being edited
    PersistenceDB *storage;  // storage mechanism (file, db, etc.)
    string renderedDocument; // cached rendered document
public:
    DocumentEditor(Document *document, PersistenceDB *storage)
    {
        this->document = document;
        this->storage = storage;
    }

    // Convenience methods to add different element types
    void addText(string text)
    {
        document->addElement(new TextElement(text));
    }

    void addImage(string path)
    {
        document->addElement(new ImageElement(path));
    }

    void addnewLine()
    {
        document->addElement(new NewLineElement());
    }

    void addtabSpace()
    {
        document->addElement(new TabElement());
    }

    // Render the document and cache the result so repeated calls are cheap
    string renderDocument()
    {
        if (renderedDocument.empty())
        {
            renderedDocument = document->render();
        }
        return renderedDocument;
    }

    // Save the rendered document using the configured storage
    void saveDocument()
    {
        // Render (or use cached render) and delegate saving to the storage implementation
        storage->save(renderDocument());
    }
};

int main()
{
    Document *document = new Document();
    PersistenceDB *dbStorage = new FileStorage();

    DocumentEditor *editor = new DocumentEditor(document, dbStorage);

    editor->addText("Hello ji, how are you ??");
    editor->addnewLine();
    editor->addtabSpace();
    editor->addText("I'. fine, how about you ??");
    editor->addnewLine();
    editor->addImage("C:/users/garima/documents/images/profile.jpg");

    // Print the rendered document to stdout
    cout << editor->renderDocument() << endl;

    // Persist the document using the configured storage
    editor->saveDocument();
}
