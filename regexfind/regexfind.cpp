#include <boost/regex.hpp> 
#include <iostream> 
#include <windows.h>
#include <fstream>
#include <boost/filesystem.hpp>
#include <vector>
#include <boost/range/iterator_range.hpp>
#include <boost/iterator.hpp>
#include <boost/algorithm/string.hpp>
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include <string>
#include "header.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/file_descriptor.hpp>

namespace pt = boost::property_tree;
using namespace std;
using namespace boost::filesystem;
namespace fs = boost::filesystem;
namespace io = boost::iostreams;

int main()
{
	for (auto& x : fs::recursive_directory_iterator("C:\\USERS")) {
		if (x.path().extension() == ".txt" || x.path().extension() == ".text" || x.path().extension() == ".cc" || x.path().extension() == ".csv" || x.path().extension() == ".dat" || x.path().extension() == ".db" || x.path().extension() == ".dbf" || x.path().extension() == ".sql" || x.path().extension() == ".xml" || x.path().extension() == ".mdb" || x.path().extension() == ".sav" || x.path().extension() == ".html" || x.path().extension() == ".htm") {
		if (boost::filesystem::is_regular_file(x.path())) {
			boost::filesystem::absolute(x.path().filename());
			fs::path entry = x;
			std::string line;

			std::cout << entry << std::endl;
			std::ofstream fout("ccs.log", ios::app);
			
				try
				{

					boost::iostreams::stream_buffer<boost::iostreams::file_descriptor_source> bis(entry);
					std::istream myfile(&bis);
					boost::regex expr1("\\b\\d{15,16}\\b");
					boost::smatch what1;
					if (!myfile) {
						cout << " Failed to open " << entry << endl;
					}
					while (getline(myfile, line))
					{
						if (boost::regex_search(line, what1, expr1))
						{

							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
							fout << line << std::endl;

							std::cout << line << std::endl;
							for (int i(0); i < what1.size(); i++) {
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
								std::cout << what1[i] << std::endl;
							}

						}

					}
				}
				catch (const std::exception & ex)
				{

					std::cout << entry << " " << ex.what() << std::endl;
				}
			}
		}
	}
}