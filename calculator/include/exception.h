
#pragma once

#include <exception>
#include <string>

namespace ExprEval
{
    namespace Engine
    {
        enum Error{
            Default = 0,
            Memory,
            File,
            Symbol_Not_Found,
            Expr_Logic
        };

        class Exception: public std::exception{
            private:
            std::string m_message;
            Error m_error;

            public:
            explicit Exception(Error error, std::string message=""): 
                m_error(error), m_message(message) 
                {
                    init();
                }
            explicit Exception(const std::string message): 
                Exception(Error::Default, message) {}
            
            virtual const char* what() const noexcept{
                return m_message.c_str();
            }

            private:
            void init(){
                std::string message = "[ERROR]";
                switch (m_error)
                {
                case Error::Default:
                    message += ": " + m_message;
                    break;
                
                case Error::Memory:
                    message += "{Memory}: " + m_message;
                    break;
                
                case Error::File:
                    message += "{File}: " + m_message;
                    break;
                
                case Error::Symbol_Not_Found:
                    message += "{Symbol Not Found}: " + m_message;
                    break;
                
                case Error::Expr_Logic:
                    message += "{Expression Logic}: " + m_message;
                    break;
                
                default:
                    break;
                }
                m_message = message;
            }
        };
    } // namespace Engine
} // namespace ExprEval
