# include <iostream>
using namespace std;

class PowerSupply {
public:
    void providePower() {
        cout << "Power Supply: Providing power..." << endl;
    }
};

class CoolingSystem {
public:
    void startFans() {
        cout << "Cooling System: Fans started..." << endl;
    }
};

class CPU {
public:
    void initialize() {
        cout << "CPU: Initialization started..." << endl;
    }
};

class Memory {
public:
    void selfTest() {
        cout << "Memory: Self-test passed..." << endl;
    }
};

class HardDrive {
public:
    void spinUp() {
        cout << "Hard Drive: Spinning up..." << endl;
    }
};

class BIOS {
public:
    void boot(CPU& cpu, Memory& memory) {
        cout << "BIOS: Booting CPU and Memory checks..." << endl;
        cpu.initialize();
        memory.selfTest();
    }
};

class OperatingSystem {
public:
    void load() {
        cout << "Operating System: Loading into memory..." << endl;
    }
};

class ComputerFacade {
private:
    PowerSupply ps;
    CoolingSystem cs;
    CPU c;
    Memory m;
    HardDrive hd;
    OperatingSystem os;
    BIOS b;
public :
    void startComputer() {
        cout << "----- Starting Computer -----" << endl;
        ps.providePower();
        cs.startFans();
        b.boot(c, m);
        hd.spinUp();
        os.load();
        cout << "Computer Booted Successfully!" << endl;
    } 
};

int main() {
    ComputerFacade* computer = new ComputerFacade();
    computer->startComputer();

    delete computer;
}