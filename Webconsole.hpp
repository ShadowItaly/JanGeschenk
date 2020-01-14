#pragma once
#include <websocketpp/config/asio_no_tls.hpp>

#include <websocketpp/server.hpp>

#include <iostream>
#include <mutex>

typedef websocketpp::server<websocketpp::config::asio> server;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

// pull out the type of messages sent by our config
typedef server::message_ptr message_ptr;

enum class color {
        white = 1,
        red = 2,
        green = 3,
        yellow = 4,
        blue = 5
};

class Webconsole
{
        private:
                websocketpp::connection_hdl _conn;
                server *s;
                std::string _flushCont;
        public:
                Webconsole(server *sk,websocketpp::connection_hdl conn) : _conn(conn),s(sk)
        {}

                template<typename ...Args,typename T>
                        void write(T s,Args... args)
                        {
                                write(s);		//Write the current param to screen
                                write(args...);	//Recursively call ourself with the rest of the params, let the compiler decide which function to call
                        }

                /**
                 * @brief The recursion anchor for _write tries to convert the argument to string to print it with a easy print string function
                 * @param argument The object to print
                 */
                template<typename T>
                        void write(T argument)
                        {
                                write(std::to_string(argument));
                        }


                void write(std::string kk)
                {
                        _flushCont+=kk;
                }

                void write(const char *k)
                {
                        _flushCont+=k;
                }

                void write(int x)
                {
                        _flushCont+=std::to_string(x);
                }

                void write(color col)
                {
                        char c = 1;
                        switch(col)
                        {
                                case color::white: c = 1;break;
                                case color::red: c = 2; break;
                                case color::green: c = 3; break;
                                case color::yellow: c = 4; break;
                                case color::blue: c = 5; break;
                                default: break;
                        }
                        
                        _flushCont+=c;
                }

                void flush()
                {
                        websocketpp::lib::error_code ec;
                        s->send(_conn,_flushCont,websocketpp::frame::opcode::value::text,ec);
                        _flushCont = "";
                }
};
