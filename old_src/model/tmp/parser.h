#ifndef MODEL_PARSER_H_
#define MODEL_PARSER_H_

#include <list>
#include <deque>
#include <memory>
#include <string>

namespace s21 {

namespace parser {

using Variable = int;
using Function = int;
using AToken = int;

using Instruction = std::deque<std::unique_ptr<AToken*>>;

std::list<Instruction> lexems_to_instructions(std::list<std::string> lexems);

std::list<std::string>
instructions_to_strings(const std::list<Instruction> &instructions);

} // namespace parser

} // namespace s21

#endif  // MODEL_PARSER_H_
