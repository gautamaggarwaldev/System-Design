# include <iostream>
using namespace std;

class ModelTrainer {
protected:
    void load() {
        cout << "Load data..." << endl;
    }
    void preprocess() {
        cout << "Preprocess data..." << endl;
    }
    virtual void train() = 0;
    virtual void evaluate() = 0;
    virtual void save() {
        cout << "Save data..." << endl;
    }

public:
    void trainPipeline(const string& path) {
        load();
        preprocess();
        train();
        evaluate();
        save();
    }
};

class NLP : public ModelTrainer {
protected:
    void train() override {
        cout << "Train data by 100 epochs by nlp" << endl;
    }

    void evaluate() override {
        cout << "Evaluate the data using nlp" << endl;
    }

    void save() override {
        cout << "Save data nlp..." << endl;
    }
};

class LLM : public ModelTrainer {
protected:
    void train() override {
        cout << "Train data by 150 epochs by llm" << endl;
    }

    void evaluate() override {
        cout << "Evaluate the data using llm" << endl;
    }
};

int main() {
    cout << "NLP training :- " << endl << endl;
    NLP* nlp = new NLP();
    nlp->trainPipeline("data/images/");
    
    cout << "LLM training :- " << endl << endl;
    LLM* llm = new LLM();
    llm->trainPipeline("data/docs/files/");
   
}
