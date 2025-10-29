#include <iostream>
using namespace std;

// Abstract Command interface: declares execute and undo operations.
class Command {
public:
    virtual void execute() = 0; // perform action
    virtual void undo() = 0;    // reverse action
    ~Command() {};              // base destructor (non-virtual here; suitable for this simple example)
};

// Receiver: Light - knows how to perform the actual operations.
class Light {
public:
    void on() {
        cout << "Light is On..." << endl;
    }

    void off() {
        cout << "Light is Off..." << endl;
    }
};

// Receiver: Fan - another concrete receiver.
// Note: placeholder selection inserted here (same output as Light::on in provided selection).
class Fan {
public:
    void on() {
        cout << "Light is On..." << endl;
    }

    void off() {
        cout << "Light is Off..." << endl;
    }
};

// Concrete Command for Light: stores a reference to a Light receiver.
class LightCommand : public Command {
private:
    Light *light;

public:
    // Constructor: bind to a Light receiver
    LightCommand(Light *l) {
        this->light = l;
    }

    // Execute forwards request to the receiver
    void execute() {
        light->on();
    }

    // Undo forwards the reverse request to the receiver
    void undo() {
        light->off();
    }
};

// Concrete Command for Fan: stores a reference to a Fan receiver.
class FanCommand : public Command {
private:
    Fan *fan;

public:
    // Constructor: bind to a Fan receiver
    FanCommand(Fan *f) {
        this->fan = f;
    }

    void execute() {
        fan->on();
    }

    void undo() {
        fan->off();
    }
};

// Invoker: RemoteController holds commands mapped to buttons and toggles them.
class RemoteController {
private:
    static const int numButtons = 4;
    Command *buttons[numButtons];   // array of command pointers for each button
    bool buttonPressed[numButtons]; // toggle state for each button
public:
    RemoteController() {
        // Initialize arrays. Note: range-for over raw arrays copies elements,
        // so using this pattern does not modify the actual arrays.
        // For correctness we explicitly initialize by index below.
        for (auto btn : buttons) {
            btn = nullptr;
        }
        for (auto btn : buttonPressed) {
            btn = false;
        }

        // Proper explicit initialization (safer and actually modifies arrays)
        for (int i = 0; i < numButtons; ++i) {
            buttons[i] = nullptr;
            buttonPressed[i] = false;
        }
    }

    // Assign a command to a button index. Replaces and deletes any previous command.
    void setCommand(int idx, Command *cmd) {
        if (idx >= 0 && idx < numButtons) {
            if (buttons[idx] != nullptr)
                delete buttons[idx]; // free previous command
            buttons[idx] = cmd;
            buttonPressed[idx] = false; // reset toggle state
        }
    }

    // Simulate pressing a button: execute or undo based on toggle state.
    void pressButton(int idx) {
        if (idx >= 0 && idx < numButtons && buttons[idx] != nullptr) {
            if (buttonPressed[idx] == false) {
                buttons[idx]->execute();
            }
            else {
                buttons[idx]->undo();
            }
            buttonPressed[idx] = !buttonPressed[idx]; // toggle state
        }
        else {
            cout << "No command assigned at button " << idx << endl;
        }
    }

    // Note: RemoteController destructor could delete remaining commands if desired.
};

// Client code: create receivers, commands, and assign them to the invoker.
int main() {
    Light *light = new Light(); // receiver
    Fan *fan = new Fan();       // receiver

    RemoteController *remote = new RemoteController(); // invoker

    // Create commands and assign to buttons
    remote->setCommand(0, new LightCommand(light));
    remote->setCommand(1, new FanCommand(fan));

    // Simulate button presses (toggle behavior)
    cout << "--- Toggling Light Button 0 ---" << endl;
    remote->pressButton(0); // ON
    remote->pressButton(0); // OFF

    cout << "--- Toggling Fan Button 1 ---" << endl;
    remote->pressButton(1); // ON
    remote->pressButton(1); // OFF

    // Press unassigned button to show default message
    cout << "--- Pressing Unassigned Button 2 ---" << endl;
    remote->pressButton(2);

    // Clean up
    delete remote;
    delete light;
    delete fan;

    return 0;
}
