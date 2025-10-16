#include "headers/queue.hpp"

void Queue::push(Token token) { this->queue.push_back(token); }

Token& Queue::pop()
{
  if (this->is_empty())
  {
    std::string msg = "attention, file vide";
    print_debug(msg);
  }

  this->temp = this->queue[0];
  this->queue.erase(this->queue.begin());
  return this->temp;
}

Token& Queue::get_first() { return this->queue[0]; }

bool Queue::is_empty() { return this->queue.empty(); }

int Queue::get_size() { return (int)(this->queue.size()); }
