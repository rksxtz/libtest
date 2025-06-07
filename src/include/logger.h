#ifndef _KW_LOGGER
#define _KW_LOGGER

#include <sys/stat.h>
#include <string>
#include <fstream>
#include <source_location>


namespace kw{

    class logger{
        public:
            enum class _log_type{
                info, warning, error
            };

            using byte_t = std::streamsize;
            using log_t = _log_type;

            explicit logger(const std::string& filename, std::ios_base::openmode _a_flag):
                _m_filename{filename}, _m_file{ _m_filename, _a_flag } {}

            explicit logger(const std::string& filename):
                logger{ filename, std::ios_base::out } { }
            
            ~logger(){
                this->_m_file.put('\n');
                this->_m_file.close();
            }

            byte_t log(const std::string& message, const log_t _log_t, const std::source_location& _src_log){
                const long int _cpos = this->_m_file.tellp();
                std::string _l_m{
                    "[" + _tostring(_log_t) + "] [" + _src_log.function_name() + " " + __TIME__ + "]"
                        + message + '\n'
                };
                this->_m_file.write(_l_m.c_str(), _l_m.size());
                return static_cast<long long int>(this->_m_file.tellp()) - _cpos;
            }

            explicit operator bool() const { return this->_m_file.good(); }
            
            const std::string& filename() const { return this->_m_filename; }
            
            std::string& filename() { return this->_m_filename; }

        private:
            std::string _m_filename;
            std::ofstream _m_file;

            inline std::string _tostring(enum log_t log){
                switch(log){
                    case log_t::info: return "info";
                    case log_t::warning: return "warning";
                    case log_t::erorr: return "error";
                    default: break;
                }
                return "unkwn";
            }
    };

}


#endif