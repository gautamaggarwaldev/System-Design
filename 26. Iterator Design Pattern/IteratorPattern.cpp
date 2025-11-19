# include <iostream>
# include <stack>
# include <vector>
using namespace std;

template<typename T>
class Iterator {
public:
    virtual bool hasNext() = 0;
    virtual T next() = 0;
};

template<typename T>
class Iterable {
public:
    virtual Iterator<T>* getIterator() = 0;
};

// LL
class LinkedList : public Iterable<int> {
public:
    int data;
    LinkedList* next;

    LinkedList(int data) {
        this->data = data;
        this->next = nullptr;
    }

    Iterator<int>* getIterator() override;
};

// BT
class BinaryTree : public Iterable<int> {
public:
    int data;
    BinaryTree* left;
    BinaryTree* right;

    BinaryTree(int data) {
        this->data = data;
        this->left = nullptr;
        this->right = nullptr;
    }

    Iterator<int>* getIterator() override;
};

// Playlist
class Song {
public:
    string title;
    string artist;

    Song(const string& title, const string& artist) {
        this->title = title;
        this->artist = artist;
    }
};

class Playlist : public Iterable<Song> {
public:
    vector<Song> songs;

    void addSong(const Song& s) {
        songs.push_back(s);
    }

    Iterator<Song>* getIterator() override;
};

class LinkedListIterator : public Iterator<int> {
private:
    LinkedList* current;
public:
    LinkedListIterator(LinkedList* head) {
        current = head;
    }
    bool hasNext() override {
        return current != nullptr;
    }
    int next() override {
        int val = current->data; 
        current = current->next;
        return val;
    }
};

class BinaryTreeInorderIterator : public Iterator<int> {
private:
    stack<BinaryTree*> st;
    BinaryTree* curr;

    void pushLefts(BinaryTree* node) {
        while (node) {
            st.push(node);
            node = node->left;
        }
    }
public:
    BinaryTreeInorderIterator(BinaryTree* root) {
        curr = root;
        pushLefts(curr);
    }

    bool hasNext() override {
        return !st.empty();
    }

    int next() override {
        BinaryTree* node = st.top();
        st.pop();
        int val = node->data;
        if (node->right) {
            pushLefts(node->right);
        }
        return val;
    }
};

class PlaylistIterator : public Iterator<Song> {
private:
    vector<Song> vec;
    size_t index;
public:
    PlaylistIterator(vector<Song> v) {
        vec = v;
        index = 0;
    }

    bool hasNext() override {
        return index < vec.size();
    }

    Song next() override {
        return vec[index++];
    }
};

// Attaching Iterators
Iterator<int>* LinkedList::getIterator() {
    return new LinkedListIterator(this);
}

Iterator<int>* BinaryTree::getIterator() {
    return new BinaryTreeInorderIterator(this);
}

Iterator<Song>* Playlist::getIterator() {
    return new PlaylistIterator(songs);
}




int main() {
    // LinkedList: 1 → 2 → 3
    LinkedList* list = new LinkedList(1);
    list->next = new LinkedList(2);
    list->next->next = new LinkedList(3);

    Iterator<int>* iterator1 = list->getIterator();

    cout << "LinkedList contents: ";

    while (iterator1->hasNext()) {
        cout << iterator1->next() << " ";
    }

    cout << "\n";


    // BinaryTree:
    //    2
    //   / \
    //  1   3
    BinaryTree* root = new BinaryTree(2);
    root->left  = new BinaryTree(1);
    root->right = new BinaryTree(3);

    Iterator<int>* iterator2 = root->getIterator();

    cout << "BinaryTree inorder: ";

    while (iterator2->hasNext()) {
        cout << iterator2->next() << " ";
    }

    cout << "\n";


    // Playlist
    Playlist playlist;
    playlist.addSong(Song("Mafia", "YYHS"));
    playlist.addSong(Song("Millionare", "YYHS"));

    Iterator<Song>* iterator3 = playlist.getIterator();

    cout << "Playlist songs:\n";

    while (iterator3->hasNext()) {
        Song s = iterator3->next();
        cout << "  " << s.title << " by " << s.artist << "\n";
    }


    delete list->next->next;
    delete list->next;
    delete list;
    delete root->left;
    delete root->right;
    delete root;
}