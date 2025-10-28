# include <iostream>
# include <vector>
# include <algorithm>
using namespace std;

class ISubscriber {
public:
    virtual void update() = 0;
    ~ISubscriber() {};
};

class IChannel {
public:
    virtual void subscribe(ISubscriber* subscriber) = 0;
    virtual void unsubscribe(ISubscriber* subscriber) = 0;
    virtual void notify() = 0;
    virtual ~IChannel() {};
};

class Channel : public IChannel {
private:
    string name;
    vector<ISubscriber*> subscribers;
    string latestVideo;

public:
    Channel(const string& name) {
        this->name = name;
    }

    void subscribe(ISubscriber* subscriber) override {
        if(find(subscribers.begin(), subscribers.end(), subscriber) == subscribers.end()) {
            subscribers.push_back(subscriber);
        }
        else {
            cout << "Already subscribed the channel!";
        }
    }

    void unsubscribe(ISubscriber* subscriber) override {
        auto it = find(subscribers.begin(), subscribers.end(), subscriber);
        if(it != subscribers.end()) {
            subscribers.erase(it);
        }
    }

    void notify() override {
        for(auto sub : subscribers) {
            sub->update();
        }
    }

    void uploadVideo(const string& title) {
        latestVideo = title;
        cout << "\n[" << name << " uploaded \"" << title << "\"]\n";
        notify();
    }

    string getLatestVideo() {
        return "\nCheckout our new Video : " + latestVideo + "\n";
    }
};

class Subscriber : public ISubscriber {
private:
    string name;
    Channel* channel;
public:
    Subscriber(const string& name, Channel* channel) {
        this->name = name;
        this->channel = channel;
    }

    // Called by Channel; prints notification message
    void update() override {
        cout << "Hey " << name << "," << this->channel->getLatestVideo();
    }
};

int main() {
    Channel* ch = new Channel("GG ki Pathshala");

    Subscriber* sub1 = new Subscriber("Garima", ch);
    Subscriber* sub2 = new Subscriber("Gautam", ch);

    ch->subscribe(sub1);
    ch->subscribe(sub2);

    ch->uploadVideo("My first video...");
    
    ch->unsubscribe(sub2);

    ch->uploadVideo("My second video...");
}
