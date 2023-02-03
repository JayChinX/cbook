
#include <iostream>
#include <ostream>
#include <string>
class PurchaseRequest {
  public:
    PurchaseRequest(const int type, const float price, const int id)
        : type(type), price(price), id(id) {}
    int getType() const { return type; }
    float getPrice() const { return price; }
    int getId() const { return id; }

  private:
    int type;
    float price = 0.f;
    int id = 0;
};

class Approver {
  public:
    void setApprover(Approver *const approver) { this->approver = approver; }

    explicit Approver(const std::string &name) : name(name) {}

    virtual void processRequest(PurchaseRequest *pur) = 0;

  protected:
    Approver *approver;
    std::string name;
};

class DepartmentApprover : public Approver {
  public:
    explicit DepartmentApprover(const std::string &name) : Approver(name) {}

    void processRequest(PurchaseRequest *pur) override {
        if (pur->getPrice() <= 5000) {
            std::cout << "请求编号id= " << pur->getId() << "被" << this->name
                      << "处理." << std::endl;
        } else {
            approver->processRequest(pur);
        }
    }
};

class CollegeApprover : public Approver {
  public:
    explicit CollegeApprover(const std::string &name) : Approver(name) {}

    void processRequest(PurchaseRequest *pur) override {
        if (pur->getPrice() > 5000 && pur->getPrice() <= 10000) {
            std::cout << "请求编号id= " << pur->getId() << "被" << this->name
                      << "处理." << std::endl;
        } else {
            approver->processRequest(pur);
        }
    }
};

class ViceSchoolMasterApprover : public Approver {
  public:
    explicit ViceSchoolMasterApprover(const std::string &name)
        : Approver(name) {}

    void processRequest(PurchaseRequest *pur) override {
        if (pur->getPrice() > 10000 && pur->getPrice() <= 30000) {
            std::cout << "请求编号id= " << pur->getId() << "被" << this->name
                      << "处理." << std::endl;
        } else {
            approver->processRequest(pur);
        }
    }
};

class SchoolMasterApprover : public Approver {
  public:
    explicit SchoolMasterApprover(const std::string &name) : Approver(name) {}

    void processRequest(PurchaseRequest *pur) override {
        if (pur->getPrice() > 30000) {
            std::cout << "请求编号id= " << pur->getId() << "被" << this->name
                      << "处理." << std::endl;
        } else {
            approver->processRequest(pur);
        }
    }
};

int main(int argc, char **argv) {
    PurchaseRequest *pur = new PurchaseRequest(1, 1000, 1);

    DepartmentApprover *department = new DepartmentApprover("张主任");
    CollegeApprover *college = new CollegeApprover("李院长");
    ViceSchoolMasterApprover *vice = new ViceSchoolMasterApprover("王副校长");
    SchoolMasterApprover *school = new SchoolMasterApprover("佟校长");

    department->setApprover(college);
    college->setApprover(vice);
    vice->setApprover(school);
    school->setApprover(department);

    vice->processRequest(pur);
    system("pause");
    return 0;
}
