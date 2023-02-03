// 享元模式

#include <initializer_list>
#include <iostream>
#include <list>
#include <map>
#include <ostream>
#include <string>
#include <utility>

class SharedState {
  public:
    friend std::ostream &operator<<(std::ostream &out, const SharedState ss) {
        return out << "[" << ss.brand << "," << ss.model << "," << ss.color
                   << "]";
    }

  public:
    SharedState(
        const std::string brand,
        const std::string model,
        const std::string color)
        : brand(brand), model(model), color(color) {}
    const std::string GetBrand() const { return brand; }
    const std::string GetModel() const { return model; }
    const std::string GetColor() const { return color; }

  private:
    std::string brand; // 品牌
    std::string model; // 型号
    std::string color; // 颜色
};

class UniqueState {
  public:
    UniqueState(const std::string owner, const std::string plates)
        : owner(owner), plates(plates){};
    const std::string GetOwner() const { return owner; }
    const std::string GetPlates() const { return plates; }
    friend std::ostream &operator<<(std::ostream &out, const UniqueState ss) {
        return out << "[" << ss.owner << "," << ss.plates << "]";
    }

  private:
    std::string owner;  // 车主
    std::string plates; // 车牌号
};

class Flyweight {
  public:
    Flyweight(const SharedState *state)
        : sharedstate(new SharedState(*state)){};
    Flyweight(const Flyweight &other)
        : sharedstate(new SharedState(*other.sharedstate)){};
    virtual ~Flyweight() {}
    SharedState *GetSharedState() const { return sharedstate; }
    void Operation(const UniqueState &state) {
        std::cout << "共享数据:" << *sharedstate << std::endl;
        std::cout << "专有数据:" << state << std::endl;
    };

  private:
    SharedState *sharedstate;
};

// class ConcreteFlyweight : public Flyweight {
//   public:
//     ConcreteFlyweight(const STATE &state) : Flyweight(state) {}

//     virtual ~ConcreteFlyweight() {}
//     virtual void Operation(STATE &state) {}
// };

class FlyweightFactory {
  public:
    FlyweightFactory(std::initializer_list<SharedState> sharedstate) {
        for (auto v : sharedstate) {
            this->flyweightMap.insert(std::make_pair<std::string, Flyweight>(
                this->GetKey(v), Flyweight(&v)));
        }
    }
    Flyweight GetFlyweight(const SharedState &ss) {
        std::string key = this->GetKey(ss);
        if (this->flyweightMap.find(key) == this->flyweightMap.end()) {
            std::cout << "车库未找到这个款式......" << std::endl;
            this->flyweightMap.insert(std::make_pair(key, Flyweight(&ss)));
            std::cout << "第一次入库成功" << std::endl;
        } else {
            std::cout << "车库找到这个款式......" << std::endl;
        }
        return this->flyweightMap.at(key);
    }

    void ListFlyweight() const {
        int count = this->flyweightMap.size();
        std::cout << "车库总信息:" << std::endl;
        for (auto pair : this->flyweightMap) {
            std::cout << pair.first << "\n";
        }
    }

  private:
    std::map<std::string, Flyweight> flyweightMap;
    std::string GetKey(const SharedState &ss) const {
        return ss.GetBrand() + '_' + ss.GetModel() + '_' + ss.GetColor();
    }
};
void AddCar(
    FlyweightFactory &ff,
    const std::string &plates,
    const std::string &owner,
    const std::string &brand,
    const std::string &model,
    const std::string &color) {
    std::cout << "车型匹配结果:" << std::endl;
    auto flyweight = ff.GetFlyweight({brand, model, color});
    flyweight.Operation({owner, plates});
}

int main() {
    FlyweightFactory f = {
        {"雪弗兰", "Camaro2020", "pink"}, {"奔驰", "C43", "black"},
        {"奔驰", "C63", "red"},           {"宝马", "M6", "red"},
        {"宝马", "X7", "white"},
    };
    f.ListFlyweight();
    std::cout << std::endl << std::endl;
    AddCar(f, "DK8888", "顽石", "宝马", "M6", "red");
    AddCar(f, "DK6666", "里奇", "宝马", "X7", "red");
    f.ListFlyweight();
    return 0;
}
