#include "../include/duckdbms.hpp"
#include "../include/texttable.hpp"
#include <fstream>

const char *errorMessage = "> your input is invalid,print \".help\" for more infomation!\n";
const char *nextLineHeader ="> ";
const char *exitMessage = "> bye!\n";
const char *dbFileName = "./db.bin";

// print help message
void DuckDBMS::printHelpMess(){
	std::cout << "*********************************************************************************************"<< std::endl << std::endl
		<<" 				Welcome to the duck_db\n 				db file locates in \"./db.bin\" "<< std::endl<< std::endl
		<<"*********************************************************************************************"<< std::endl
		<<"  .help 							print help message;"<< std::endl
		<<"  .exit 							exit program;"<< std::endl
		<<"  .reset 							delete db file;"<< std::endl
		<<"  insert db {index} {name} {age} {email}; 			insert record;"<< std::endl
		<<"  delete from db where id ={index}; 				delete record;"<< std::endl
		<<"  update db {name} {age} {email} where id={index}; 		update a record;"<< std::endl
		<<"  select * from db where id={index}; 				search a record by index;"<< std::endl
		<<"  select * from db where id in({minIndex},{maxIndex}); 		search records between indexs;"<< std::endl
		<<"*********************************************************************************************"<< std::endl
		<< std::endl << nextLineHeader;
}

// int to key_t
void DuckDBMS::intToKeyT(BPLUSTREE::BplusTree::key_t *a,int *b) {
	char key[16] = { 0 };
	sprintf(key, "%d", *b);
	*a = key;
}

bool DuckDBMS::is_file_exist(const char *fileName) {
    std::ifstream ifile(fileName);
  	return ifile.good();
}

// print table
void DuckDBMS::printTable(int *index, BPLUSTREE::BplusTree::value_t *values){
	TextTable t;

    t.add( " id " );
    t.add( " name " );
    t.add( " age " );
    t.add( " email " );
    t.endOfRow();

    t.add( std::to_string(*index) );
    t.add( values ->name );
    t.add( std::to_string(values ->age));
    t.add( values ->email );
    t.endOfRow();

    std::cout << t << std::endl;
}

DuckDBMS::DuckDBMS() {
    initialSystem();
}

// initial
void DuckDBMS::initialSystem(){
	// step 1 : print help message
	printHelpMess();
	// step 2 : initial database from file
	m_duck_db_ptr.reset(new BPLUSTREE::BplusTree(dbFileName, !is_file_exist(dbFileName)));
	// step 3 : REPL select commdand (insert,delete,update,search)
	selectCommand();
}

// insert
int DuckDBMS::insertRecord(int *index, BPLUSTREE::BplusTree::value_t *values){
	
	BPLUSTREE::BplusTree::key_t key;
	intToKeyT(&key,index);
	return m_duck_db_ptr->insert(key, *values);
}

// delete 
int DuckDBMS::deleteRecord(int *index){
	BPLUSTREE::BplusTree::key_t key;
	intToKeyT(&key,index);
    return m_duck_db_ptr->remove(key);
}

// update
int DuckDBMS::updateRecord(int *index, BPLUSTREE::BplusTree::value_t *values){
	BPLUSTREE::BplusTree::key_t key;
	intToKeyT(&key,index);
	return m_duck_db_ptr->update(key, *values);
}

// search by index
int DuckDBMS::searchRecord(int *index, BPLUSTREE::BplusTree::value_t *return_val){
	BPLUSTREE::BplusTree::key_t key;
	intToKeyT(&key,index);
	return m_duck_db_ptr->search(key, return_val); 
}

// search all
void DuckDBMS::searchAll(int *start, int *end){
	TextTable t;
    t.add( " id " );
    t.add( " name " );
    t.add( " age " );
    t.add( " email " );
    t.endOfRow();

	BPLUSTREE::BplusTree::key_t key;
	BPLUSTREE::BplusTree::value_t *return_val = new BPLUSTREE::BplusTree::value_t;

	for (int i = *start; i <= *end; ++i) {
		intToKeyT(&key,&i);
		int return_code = m_duck_db_ptr->search(key, return_val);
		switch(return_code){
			case -1:
			// no exist
				break;
			case 0:
			// find
				t.add( std::to_string(i) );
			    t.add( return_val ->name );
			    t.add( std::to_string(return_val ->age));
			    t.add( return_val ->email );
			    t.endOfRow();
				break;
			case 1:
			// deleted
				break;
		}
	}
    delete return_val;
	std::cout << t << std::endl;
}

// select command
void DuckDBMS::selectCommand(){
	// REPL read-execute-print loop
	char *userCommand = new char[256];
	
	while(true){
		std::cin.getline(userCommand,256);
		
		if(strcmp(userCommand,".exit") == 0){
	    	std::cout << exitMessage;
			break;
	    } else if(strcmp(userCommand,".help") == 0){
	    	printHelpMess();

	    }else if(strcmp(userCommand,".reset") == 0){
	    	if(remove( dbFileName) != 0)
	    		std::cout<< "can't delete file"<< "\n" << nextLineHeader;
	    	else
				std::cout << "DB file has been deleted!"<< std::endl << std::endl;
	    	initialSystem();
	    
        }else if(strncmp(userCommand,"insert",6) == 0){
	    	int *keyIndex = new int;
	    	BPLUSTREE::BplusTree::value_t *insertData = new BPLUSTREE::BplusTree::value_t;

	    	int okNum = sscanf(userCommand,"insert db %d %s %d %s;", keyIndex, insertData->name, &(insertData->age), insertData->email);
			if(okNum < 3){
				std::cout << errorMessage << nextLineHeader;
			}else{
				int return_code = insertRecord(keyIndex, insertData);

				if (return_code == 0){
					std::cout << "> executed insert index:"<< *keyIndex << "\n" << nextLineHeader;
				}else if(return_code == 1){
					std::cout << "> failed: already exist index:"<< *keyIndex << "\n"<< nextLineHeader;
				}else{
					std::cout << "> failed!\n"<< nextLineHeader;
				}
			}
            delete keyIndex;
            delete insertData;

	    }else if(strncmp(userCommand,"delete",6) == 0){
	    	int *keyIndex = new int;

	    	int okNum = sscanf(userCommand,"delete from db where id=%d;", keyIndex);
			if(okNum < 1){
				std::cout << errorMessage<< nextLineHeader;
			}else{
				int return_code = deleteRecord(keyIndex);
				if (return_code == 0){
					std::cout << "> executed delete index:"<< *keyIndex << "\n" << nextLineHeader;
				}else if(return_code == -1){
					std::cout << "> failed ! no index:"<< *keyIndex << "\n"<< nextLineHeader;
				}else{
					std::cout << "> failed!\n" << nextLineHeader;
				}
			}

            delete keyIndex;

	    }else if(strncmp(userCommand,"select",6) == 0){

	    	if( ! strstr (userCommand,"=")){
	    		int i_start,i_end;

	    		int okNum = sscanf(userCommand,"select * from db where id in(%d,%d);", &i_start, &i_end);
				if(okNum < 2){
					std::cout << errorMessage << nextLineHeader;
				}else{
					searchAll(&i_start, &i_end);
					std::cout << "> executed search" << "\n" << nextLineHeader;
                }

	    	}else{
		    	int *keyIndex = new int;
		    	int okNum = sscanf(userCommand,"select * from db where id=%d;", keyIndex);
				if(okNum < 1){
					std::cout << errorMessage<< nextLineHeader;
				}else{
					BPLUSTREE::BplusTree::value_t *return_val = new BPLUSTREE::BplusTree::value_t;

					int return_code = searchRecord(keyIndex, return_val);
					if (return_code != 0){
						std::cout << "> index:"<< *keyIndex << " doesn't exist" << "\n" << nextLineHeader;
					}else{
						printTable( keyIndex , return_val);
						std::cout << "> executed search" << "\n" << nextLineHeader;
					}

                    delete return_val;
				}

                delete keyIndex;
			}

	    }else if(strncmp(userCommand,"update",6) == 0){

	    	int *keyIndex = new int;
	    	BPLUSTREE::BplusTree::value_t *updateData = new BPLUSTREE::BplusTree::value_t;

	    	int okNum = sscanf(userCommand,"update db %s %d %s where id=%d;", 
	    		 updateData->name,&(updateData->age),updateData->email,keyIndex);

			if(okNum < 3){
				std::cout << errorMessage<< nextLineHeader;
			}else{
				int return_code = updateRecord(keyIndex, updateData);

				if (return_code == 0){
					std::cout << "> executed update index:"<< *keyIndex << "\n" << nextLineHeader;
				}else{
					std::cout << "> failed! no index:"<< *keyIndex << "\n" << nextLineHeader;
				}
			}

            delete keyIndex;
            delete updateData;
	    }
	    else{
	    	std::cout << errorMessage << nextLineHeader;
	    }
	}


}