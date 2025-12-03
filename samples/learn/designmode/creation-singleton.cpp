
// 创建型-单例模式
// 定义：单例模式是一种对象创建模式，使用单例模式，可以保证为一个类生成唯一的实例对象。
// GoF
// 对单例的定义：保证一个类只有一个实例存在，同时提供该对象实例加以访问的全局访问方法。

// 使用单例模式的原因
// 在应用系统开发中，我们常常有以下需求：

// 1. 多个线程公用一个socket资源，或者操作同一个对象
// 2. 在整个程序空间需要使用全局变量，共享资源
// 3. 大规模系统中，为了性能考虑，需要节省对象创建的时间等

// 实现步骤：
// 1. 构造函数私有化
// 2. 提供一个全局的静态方法(全局访问点)
// 3. 在类中定义一个静态指针，指向本类的变量的静态变量指针

#include <atomic>
#include <cstddef>
#include <iostream>
#include <mutex>
#include <ostream>
#include <thread>
class Singleton {
  private:
    Singleton() {
        std::cout << "Sluggard singleton construct start." << std::endl;
    }

  public:
    // 懒汉模式，每次获取都要判断。多线程不安全
    // 懒汉式，只有在使用的时候才会去创建
    // 存在的问题，多个线程同时首次调用时，可能会出现创建多次的问题(导致内存泄漏)
    // static Singleton *getInstance(void) {
    //     if (NULL == m_psl) { m_psl = new Singleton; }
    //     return m_psl;
    // }
    // 饿汉
    // static Singleton *getInstance1(void) {
    //     // 饿汉不需要判断
    //     return m_psl1;
    // }
    //双重检测锁
    static Singleton *getInstance2(void) {
        static std::mutex m_mutex;
        Singleton *tmp = m_psl2.load();
        if (NULL == m_psl) {
            std::lock_guard<std::mutex> lock(m_mutex);
            tmp = m_psl2.load();
            // 临界区（Critical
            // Section）。临界区对象通过提供一个进程内所有线程必须
            // 共享的对象来控制线程。只有拥有那个对象的线程可以访问保护资源。在另一个线
            // 程可以访问该资源之前，前一个线程必须释放临界区对象，以便新的线程可以索取对象的访问权

            // lock里面判断一次，因为可能有多个线程在lock处等待，一个成功之后，
            // 会将m_psl设置为非空，这样下个线程就算拿到lock资源，再进去发现指针非空就离开了
            // lock外判断一次，是因为获取锁，是很浪费时间的，获取锁之外还有一层判断，那么在第二次获取单例对象的时候，
            // lock外的if判断发现指针已经非空，就不会再获取锁了，直接返回了对应的对象，这样双层检测，即保证了对象创建的唯一性，又减少了获取锁浪费的时间和资源

            if (NULL == tmp) {
                tmp = new Singleton;
                m_psl2.store(tmp);
            }
        }

        return tmp;
    }
    static Singleton *getInstance3(void) {
        static std::mutex m_mutex;
        if (NULL == m_psl) {
            m_mutex.lock();
            // 临界区（Critical
            // Section）。临界区对象通过提供一个进程内所有线程必须
            // 共享的对象来控制线程。只有拥有那个对象的线程可以访问保护资源。在另一个线
            // 程可以访问该资源之前，前一个线程必须释放临界区对象，以便新的线程可以索取对象的访问权

            // lock里面判断一次，因为可能有多个线程在lock处等待，一个成功之后，
            // 会将m_psl设置为非空，这样下个线程就算拿到lock资源，再进去发现指针非空就离开了
            // lock外判断一次，是因为获取锁，是很浪费时间的，获取锁之外还有一层判断，那么在第二次获取单例对象的时候，
            // lock外的if判断发现指针已经非空，就不会再获取锁了，直接返回了对应的对象，这样双层检测，即保证了对象创建的唯一性，又减少了获取锁浪费的时间和资源

            if (NULL == m_psl) {
                m_psl = new Singleton;
            }
            m_mutex.unlock();
        }

        return m_psl;
    }

    static void FreeInstance() {
        if (NULL != m_psl) {
            delete m_psl;
            m_psl = NULL;
        }
        // if (NULL != m_psl1) {
        //     delete m_psl1;
        //     m_psl1 = NULL;
        // }
        // Singleton *tmp = m_psl2.load();
        // if (NULL != tmp) {
        //     delete m_psl2;
        //     m_psl2 = NULL;
        // }
    }

  private:
    static Singleton *m_psl;
    // static Singleton *m_psl1;
    // 双重检测锁
    static std::atomic<Singleton *> m_psl2;
};
// 静态变量初始化的方法，要放到类的外面
// 懒汉
Singleton *Singleton::m_psl = NULL;
// 饿汉
// Singleton *Singleton::m_psl1 = new Singleton;
// 双重检测锁
std::atomic<Singleton *> Singleton::m_psl2;

// 懒汉式因为使用的时候才会创建内存，所以当多个线程同时使用的时候可能会出现多次创建的问题，饿汉式不存在这个问题。

// 懒汉式虽然有有点，但是每次调用GetInstance()静态方法都必须判断静态指针是否为NULL使程序相对开销增大，多喜爱能成中会导致多个实例产生，从而导致运行代码不正确以及内存泄漏，也有可能是多次释放资源。

// 这是因为C++中构造函数并不是线程安全的，C++中的构造函数简单分为两步

// 内存分配
// 初始化成员变量
// 由于多线程的关系，可能内存放分配好，还没有给成员赋值，就发生了线程切换，导致下个线程中又申请了一遍内存。

void fun() {
    Singleton *p1 = Singleton::getInstance3();
    std::cout << std::this_thread::get_id() << "-"  << std::endl;
}

int main(int argc, char *const argv[]) {
    // Singleton *p1 = Singleton::getInstance2();
    // Singleton *p2 = Singleton::getInstance2();
    // if (p1 == p2) {
    //     std::cout << "p1 equal p2" << std::endl;
    // } else {
    //     std::cout << "p1 not equal p2" << std::endl;
    // }
    std::thread t(fun);
    std::thread t1(fun);
    t.join();
    t1.join();
    Singleton::FreeInstance();
    return 0;
}