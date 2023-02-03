// 结构型-桥接

#include <iostream>
#include <ostream>
#include <string>
class Color {
  public:
    virtual void FillColor() = 0;
};

class Red : public Color {
  public:
    Red() : colorType("Red") {}
    void FillColor() override {
        std::cout << "填充颜色:" << colorType << std::endl;
    }

  private:
    std::string colorType;
};

class Blue : public Color {
  public:
    Blue() : colorType("Red") {}
    void FillColor() override {
        std::cout << "填充颜色:" << colorType << std::endl;
    }

  private:
    std::string colorType;
};

class Shape {
  public:
    virtual void ShowShape() = 0;
    virtual void SetColor(Color *color) = 0;

  protected:
    virtual void DrawShape() = 0;
    virtual void DrawColor() = 0;
    Color *color;
};

class Circle : public Shape {
  public:
    Circle() : shapeType("Circle") {}
    void ShowShape() override {
        DrawShape();
        DrawColor();
    }
    void SetColor(Color *color) override { this->color = color; }

  private:
    void DrawShape() override {
        std::cout << "绘制:" << shapeType << std::endl;
    }
    void DrawColor() override { this->color->FillColor(); }
    std::string shapeType;
};

class Rectangle : public Shape {
  public:
    Rectangle() : shapeType("Rectangle") {}
    void ShowShape() override {
        DrawShape();
        DrawColor();
    }
    void SetColor(Color *color) override { this->color = color; }

  private:
    void DrawShape() override {
        std::cout << "绘制:" << shapeType << std::endl;
    }
    void DrawColor() override { this->color->FillColor(); }
    std::string shapeType;
};

int main() {
    std::cout << "绘制不同的圆" << std::endl;
    Shape *shape = new Circle;
    shape->SetColor(new Red);
    shape->ShowShape();

    shape->SetColor(new Blue);
    shape->ShowShape();

    delete shape;

    std::cout << "绘制不同的矩形:" << std::endl;
    shape = new Rectangle;
    shape->SetColor(new Red);
    shape->ShowShape();

    shape->SetColor(new Blue);
    shape->ShowShape();

    return 0;
}