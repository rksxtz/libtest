#ifndef _LOGGER
#define _LOGGER

#include <sys/stat.h>

#include <cstdio>

#include <string>

#include <iostream>


namespace kw{

    class logger{
        public:
            explicit logger(const std::string& filename):
                filename{ filename } {
                    this->file = fopen(this->filename.c_str(), "a+");
                }

            void write(const std::string& message, const std::string& _func){
                std::string _w_buffer{
                    std::string{__TIME__} + " " + _func + "() : " + message + '\n'
                };
                if(fwrite(_w_buffer.c_str(), 1, _w_buffer.size(), this->file))
                    perror("Unable to write log using kw::logger");
            }

            std::string last_log(){
                std::string _llog{};
                [&]() -> void{
                    FILE* _rfile = fopen(this->filename.c_str(), "rb");
                    fseek(_rfile, 0, SEEK_END);
                    long int position = ftell(this->file);
                    while(--position >= 0){
                        char ch{};
                        fseek(_rfile, position, SEEK_SET);
                        ch = fgetc(_rfile);
                        if(ch == '\n')
                            break;
                        _llog = ch + _llog;
                    }
                    if(position < 0){
                        char _buffer[BUFSIZ];
                        fgets(_buffer, BUFSIZ, _rfile);
                        _llog = static_cast<std::string&&>(std::string{ _buffer });
                    }
                    fclose(_rfile);
                }();
                return static_cast<std::string&&>(_llog);
            }

            void close(){
                this->~logger();
            }

            ~logger(){
                fputc('\n', this->file);
                fclose(this->file);
            }


        private:
            const std::string filename;
            FILE* file;
    };

}


#endif