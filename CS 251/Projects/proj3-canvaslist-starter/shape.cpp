#include "include/shape.h"

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

Shape::Shape() {
  x = 0;
  y = 0;
}

Shape::Shape(int x, int y) {
  this->x = x;
  this->y = y;
}

Shape::~Shape() {
  // delete this;
}

Shape* Shape::copy() {
  Shape* newShape = new Shape;
  newShape->setX(this->x);
  newShape->setY(this->y);

  return newShape;
}

int Shape::getX() const {
  return this->x;
}

int Shape::getY() const {
  return this->y;
}

void Shape::setX(int x) {
  this->x = x;
}

void Shape::setY(int y) {
  this->y = y;
}

string Shape::as_string() const {
  string complete =
      "It's a Shape at x: " + to_string(this->x) + ", y: " + to_string(this->y);
  return complete;
}

Circle::Circle() {
  // Shape();
  radius = 0;
}

Circle::Circle(int r) {
  // Shape();
  radius = r;
}

Circle::Circle(int x, int y, int r) {
  setX(x);
  setY(y);
  radius = r;
}

Circle::~Circle() {
}

Circle* Circle::copy() {
  return new Circle(x, y, radius);
}

int Circle::getRadius() const {
  return radius;
}

void Circle::setRadius(int r) {
  radius = r;
}

string Circle::as_string() const {
  string complete = "It's a Circle at x: " + to_string(this->x) +
                    ", y: " + to_string(this->y) +
                    ", radius: " + to_string(radius);
  return complete;
}

Rect::Rect() {
  width = 0;
  height = 0;
}

Rect::Rect(int w, int h) {
  width = w;
  height = h;
}

Rect::Rect(int x, int y, int w, int h) {
  setX(x);
  setY(y);
  setWidth(w);
  setHeight(h);
}

Rect::~Rect() {
}

Rect* Rect::copy() {
  return new Rect(x, y, width, height);
}

int Rect::getWidth() const {
  return width;
}

int Rect::getHeight() const {
  return height;
}

void Rect::setWidth(int w) {
  width = w;
}

void Rect::setHeight(int h) {
  height = h;
}

string Rect::as_string() const {
  string complete = "It's a Rectangle at x: " + to_string(this->x) +
                    ", y: " + to_string(this->y) +
                    " with width: " + to_string(width) +
                    " and height: " + to_string(height);
  return complete;
}

RightTriangle::RightTriangle() {
  base = 0;
  height = 0;
}

RightTriangle::RightTriangle(int b, int h) {
  setBase(b);
  setHeight(h);
}

RightTriangle::RightTriangle(int x, int y, int b, int h) {
  setX(x);
  setY(y);
  setBase(b);
  setHeight(h);
}

RightTriangle::~RightTriangle() {
}

RightTriangle* RightTriangle::copy() {
  return new RightTriangle(x, y, base, height);
}

int RightTriangle::getBase() const {
  return base;
}

int RightTriangle::getHeight() const {
  return height;
}

void RightTriangle::setBase(int b) {
  base = b;
}

void RightTriangle::setHeight(int h) {
  height = h;
}

string RightTriangle::as_string() const {
  string complete = "It's a Right Triangle at x: " + to_string(this->x) +
                    ", y: " + to_string(this->y) +
                    " with base: " + to_string(base) +
                    " and height: " + to_string(height);
  return complete;
}
