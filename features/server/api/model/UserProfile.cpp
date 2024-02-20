#include "UserProfile.h"

UserProfile::UserProfile() : name(UserName()), nick("") {}

UserProfile::UserProfile(UserName name, int age, double money) : name(name), age(age), money(money) {}

UserName::UserName() {}
UserName::UserName(const std::string &name) : name(name) {}