#include <functional>
#include <variant>
#include <string>
#include <utility>
#include <iostream>

#ifndef FLOW_H
#define FLOW_H

namespace flow{

    template<typename T>
    class FlowChainer{
        private:
            unsigned int error_code=0;
            T succesful_result{};
        public:
            FlowChainer() {
                this->error_code = 1;
            }

            explicit FlowChainer(T&& function_result) {
                this->succesful_result = std::forward<T>(function_result);
            }

            operator int() const { return error_code; }
            template<typename U>
            FlowChainer<U> then(std::function<std::variant<U, std::string>(T)> function_to_chain){
                if(this->error_code != 0){
                    return FlowChainer<U>();
                } else {
                    auto result = function_to_chain(this->succesful_result);
                    if(result.index() == 0){
                        return FlowChainer<U>(std::move(std::get<0>(result)));
                    } else {
                        this->error_code = 1;
                        std::cerr << std::get<1>(result) << "\n" ;
                        return FlowChainer<U>();
                    }
                }
            }
    };

    class FlowStarter{
        private:
            unsigned int error_code=0;
        public:
            operator int() const {return error_code;}
            template<typename U>
            FlowChainer<U> first(std::function<std::variant<U, std::string>()> first_function){
                auto result = first_function();
                if(result.index() == 0){
                    return FlowChainer<U>(std::move(std::get<0>(result)));
                } else {
                    this->error_code = 1;
                    std::cerr << std::get<1>(result) << "\n" ;
                    return FlowChainer<U>();
                }
            }
    };

}
#endif