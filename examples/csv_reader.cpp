
#include"fast-cpp-csv-parser/csv.h"
#include<iostream>

int main(){
    io::CSVReader<4> in("/Users/rdgsljtc/Desktop/Git/Machine-Learning/data/lifesat/oecd_bli_2015.csv");
    in.read_header(io::ignore_extra_column, "\"INEQUALITY\"","\"INDICATOR\"", "\"Country\"", "\"Value\"");
    std::string country, indicator, inequality; double lifesat;
    while(in.read_row(inequality, indicator, country, lifesat)){
        if (indicator == "\"SW_LIFS\""){
            if (inequality == "\"TOT\""){
                std::cout << "Country = " << country << " Life Satisfaction = " << lifesat << std::endl;
            }
        }
    }
}
