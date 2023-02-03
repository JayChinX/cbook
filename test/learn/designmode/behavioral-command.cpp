
#include <iostream>
#include <queue>
#include <unistd.h>

class HandleClinetProtocal {
  public:
    void AddMoney() { std::cout << "给玩家增加金币" << std::endl; }

    void AddDiamond() { std::cout << "给玩家增加钻石" << std::endl; }

    void AddEquipment() { std::cout << "给玩家穿装备" << std::endl; }

    void AddLevel() { std::cout << "给玩家升级" << std::endl; }
};

class AbstractCommand {
  public:
    virtual void handle() = 0;
};

class AddMoneyCommand : public AbstractCommand {
  public:
    AddMoneyCommand(HandleClinetProtocal *proto) { this->proto = proto; }

    void handle() override { proto->AddMoney(); }

  private:
    HandleClinetProtocal *proto;
};

class AddDiamondCommand : public AbstractCommand {
  public:
    AddDiamondCommand(HandleClinetProtocal *proto) { this->proto = proto; }

    void handle() override { proto->AddDiamond(); }

  private:
    HandleClinetProtocal *proto;
};

class AddEquipmentCommand : public AbstractCommand {
  public:
    AddEquipmentCommand(HandleClinetProtocal *proto) { this->proto = proto; }

    void handle() override { proto->AddEquipment(); }

  private:
    HandleClinetProtocal *proto;
};

class AddLevelCommand : public AbstractCommand {
  public:
    AddLevelCommand(HandleClinetProtocal *proto) { this->proto = proto; }

    void handle() override { proto->AddLevel(); }

  private:
    HandleClinetProtocal *proto;
};

class Server {
  public:
    void AddRequest(AbstractCommand *command) { commands.push(command); }

    void Run() {
        while (!commands.empty()) {
            sleep(2);
            AbstractCommand *command = commands.front();
            command->handle();
            commands.pop();
        }
    }

    std::queue<AbstractCommand *> commands;
};

int main() {
    HandleClinetProtocal *proto = new HandleClinetProtocal;

    AbstractCommand *addmony = new AddMoneyCommand(proto);
    AbstractCommand *adddiamond = new AddDiamondCommand(proto);
    AbstractCommand *addequipment = new AddEquipmentCommand(proto);
    AbstractCommand *addlevel = new AddLevelCommand(proto);
    Server *server = new Server;
    server->AddRequest(addmony);
    server->AddRequest(adddiamond);
    server->AddRequest(addequipment);
    server->AddRequest(addlevel);

    server->Run();
    return 0;
}