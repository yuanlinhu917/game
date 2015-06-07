/******************************************************************************/
#include "Csv_Reader.h"
#include "ace/Assert.h"
#include "ace/OS.h"
#include <boost/lexical_cast.hpp>
#include "MF_Log.h"
/******************************************************************************/
Csv_Reader::Csv_Field::Csv_Field(CSV_FIELD_TYPE type)
{
	field_type = type;
	field_value = new Csv_Field_Value();
	ACE_ASSERT(field_value != NULL);
	if (field_value == NULL)
	{
		//MF_ERROR("Csv_Field  field_value = 0 \n");
		return;
	}
	switch(type)
	{
	case CSV_FIELD_TYPE_FLOAT:
		break;
	case CSV_FIELD_TYPE_INT:
		break;
	case CSV_FIELD_TYPE_BIN:
		field_value->bin_data.bin_data = new char[MAX_BIN_DATA_SIZE];
		field_value->bin_data.data_size = 0;
		ACE_ASSERT(field_value->bin_data.bin_data != NULL);
		if (field_value->bin_data.bin_data == NULL)
		{
			MF_ERROR("Csv_Field  bin_data = 0 \n");
		}
		break;
	case CSV_FIELD_TYPE_STRING:
		field_value->text = new char[MAX_TEXT_DATA_SIZE];
		ACE_ASSERT(field_value->text != NULL);
		if (field_value->text == NULL)
		{
			MF_ERROR("Csv_Field string = 0 \n");
		}
		break;
	case CSV_FIELD_TYPE_TEXT:
		field_value->text = new char[MAX_STRING_DATA_SIZE];
		ACE_ASSERT(field_value->text != NULL);
		if (field_value->text == NULL)
		{
			MF_ERROR("Csv_Field  text = 0 \n");
		}
		break;
	default:
		ACE_ASSERT(0);
		MF_ERROR("Csv_Field  err \n");
		break;
	}
}
//-----------------------------------------------------------------------------
Csv_Reader::Csv_Field::~Csv_Field()
{
	switch(field_type)
	{
	case CSV_FIELD_TYPE_FLOAT:
	case CSV_FIELD_TYPE_INT:
		break;
	case CSV_FIELD_TYPE_BIN:
		delete[] field_value->bin_data.bin_data;
		field_value->bin_data.bin_data = NULL;
		field_value->bin_data.data_size = 0;
		break;
	case CSV_FIELD_TYPE_STRING:
	case CSV_FIELD_TYPE_TEXT:
		delete[] field_value->text;
		field_value->text = NULL;
		break;
	default:
		ACE_ASSERT(0);
		MF_ERROR("Csv_Field  err \n");
		break;
	}
	delete field_value;
}

//-----------------------------------------------------------------------------
bool Csv_Reader::Csv_Field::get_double( double& float_value )
{
	if (field_type != CSV_FIELD_TYPE_FLOAT)
	{
		MF_ERROR("Csv_Field::get_double err\n");
		ACE_ASSERT(false);
		return false;
	}
	float_value = field_value->double_value;
	return true;
}
//-----------------------------------------------------------------------------
bool Csv_Reader::Csv_Field::get_int64( int64_t& int_value )
{
	if (field_type != CSV_FIELD_TYPE_INT)
	{
		MF_ERROR("Csv_Field::get_int64 err\n");
		ACE_ASSERT(false);
		return false;
	}
	int_value = field_value->long64_value;
	return true;
}
//-----------------------------------------------------------------------------
bool Csv_Reader::Csv_Field::get_string( char* string_data )
{
	if (field_type != CSV_FIELD_TYPE_STRING)
	{
		MF_ERROR("Csv_Field::get_string err\n");
		ACE_ASSERT(false);
		return false;
	}
	strncpy(string_data,field_value->text,strlen(field_value->text));
	return true;
}
//-----------------------------------------------------------------------------
bool Csv_Reader::Csv_Field::get_bin( char* bin_data,int32_t&size )
{
	if (field_type != CSV_FIELD_TYPE_BIN)
	{
		MF_ERROR("Csv_Field::get_bin err\n");
		ACE_ASSERT(false);
		return false;
	}
	size = field_value->bin_data.data_size;
	memcpy(bin_data,field_value->bin_data.bin_data,size);
	return true;
}
//-----------------------------------------------------------------------------
bool Csv_Reader::Csv_Field::to_float( float& flt_val )
{
	if (field_type != CSV_FIELD_TYPE_FLOAT)
	{
		MF_ERROR("Csv_Field::to_float err\n");
		ACE_ASSERT(false);
		return false;
	}
    flt_val = ::boost::lexical_cast< float >(field_value->double_value);
	return true;
}
//-----------------------------------------------------------------------------
bool Csv_Reader::Csv_Field::to_double( double& flt_val )
{
	if (field_type != CSV_FIELD_TYPE_FLOAT)
	{
		MF_ERROR("Csv_Field::to_double err\n");
		ACE_ASSERT(false);
		return false;
	}
	flt_val = field_value->double_value;
	return true;
}
//-----------------------------------------------------------------------------
bool Csv_Reader::Csv_Field::to_int8( int8_t& int_val )
{
	if (field_type != CSV_FIELD_TYPE_INT)
	{
		MF_ERROR("Csv_Field::to_int8 err\n");
		ACE_ASSERT(false);
		return false;
	}
	int_val = (int8_t)(field_value->long64_value);
	return true;
}
//-----------------------------------------------------------------------------
bool Csv_Reader::Csv_Field::to_uint8( uint8_t& int_val )
{
	if (field_type != CSV_FIELD_TYPE_INT)
	{
		MF_ERROR("Csv_Field::to_uint8 err\n");
		ACE_ASSERT(false);
		return false;
	}
	int_val = (uint8_t)(field_value->long64_value);
	return true;
}
//-----------------------------------------------------------------------------
bool Csv_Reader::Csv_Field::to_int16( int16_t& int_val )
{
	if (field_type != CSV_FIELD_TYPE_INT)
	{
		MF_ERROR("Csv_Field::int16_t err\n");
		ACE_ASSERT(false);
		return false;
	}
	int_val = ::boost::lexical_cast< int16_t >(field_value->long64_value);
	return true;
}
//-----------------------------------------------------------------------------
bool Csv_Reader::Csv_Field::to_uint16( uint16_t& int_val )
{
	if (field_type != CSV_FIELD_TYPE_INT)
	{
		MF_ERROR("Csv_Field::uint16_t err\n");
		ACE_ASSERT(false);
		return false;
	}
	int_val = ::boost::lexical_cast< uint16_t >(field_value->long64_value);
	return true;
}
//-----------------------------------------------------------------------------
bool Csv_Reader::Csv_Field::to_int32( int32_t& int_val )
{
	if (field_type != CSV_FIELD_TYPE_INT)
	{
		MF_ERROR("Csv_Field::to_int32 err\n");
		ACE_ASSERT(false);
		return false;
	}
	int_val = ::boost::lexical_cast< int32_t >(field_value->long64_value);
	return true;
}
//-----------------------------------------------------------------------------
bool Csv_Reader::Csv_Field::to_uint32( uint32_t& int_val )
{
	if (field_type != CSV_FIELD_TYPE_INT)
	{
		MF_ERROR("Csv_Field::to_uint32 err\n");
		ACE_ASSERT(false);
		return false;
	}
	int_val = ::boost::lexical_cast< uint32_t >(field_value->long64_value);
	return true;
}
//-----------------------------------------------------------------------------
bool Csv_Reader::Csv_Field::to_int64( int64_t& int_val )
{
	if (field_type != CSV_FIELD_TYPE_INT)
	{
		MF_ERROR("Csv_Field::to_int64 err\n");
		ACE_ASSERT(false);
		return false;
	}
	int_val = field_value->long64_value;
	return true;
}
//-----------------------------------------------------------------------------
bool Csv_Reader::Csv_Field::to_uint64( uint64_t& int_val )
{
	if (field_type != CSV_FIELD_TYPE_INT)
	{
		ACE_ASSERT(false);
		MF_ERROR("Csv_Field::to_uint64 err\n");
		return false;
	}
	int_val = ::boost::lexical_cast< uint64_t >(field_value->long64_value);
	return true;
}
//-----------------------------------------------------------------------------
bool Csv_Reader::Csv_Field::text_to_string( std::string& str_val )
{
	if (field_type == CSV_FIELD_TYPE_STRING || field_type == CSV_FIELD_TYPE_TEXT )
	{
		str_val = field_value->text;
		return true;
	}
	ACE_ASSERT(false);
	MF_ERROR("Csv_Field::text_to_string err\n");
	return false;
	
}
//-----------------------------------------------------------------------------
bool Csv_Reader::Csv_Field::bin_to_string( std::string& bin_val )
{
	if (field_type == CSV_FIELD_TYPE_BIN)
	{
		bin_val.assign(field_value->bin_data.bin_data, field_value->bin_data.data_size);
		return true;
	}
	ACE_ASSERT(false);
	MF_ERROR("Csv_Field::bin_to_string err\n");
	return false;
}
//-----------------------------------------------------------------------------
Csv_Reader::Csv_Reader()
{
	separator_type_ = CSV_SEPARTOR_COMMA;
	
	separator_[CSV_SEPARTOR_COMMA] = ",";
	separator_[CSV_SEPARTOR_TAB] = "	";
	separator_[CSV_SEPARTOR_ENCODE] =" ";

	field_type_text[CSV_FIELD_TYPE_FLOAT] = "FLOAT";
	field_type_text[CSV_FIELD_TYPE_INT] = "INT";
	field_type_text[CSV_FIELD_TYPE_BIN] = "BIN";
	field_type_text[CSV_FIELD_TYPE_TEXT] = "TEXT";
	field_type_text[CSV_FIELD_TYPE_STRING] = "STRING";


	data_col_count_ = 0;
	data_row_count_ = 0;
}
//-----------------------------------------------------------------------------
Csv_Reader::~Csv_Reader()
{
	destroy();
}
//-----------------------------------------------------------------------------
bool Csv_Reader::create(  const std::string& dir,const std::string& file_name)
{
    destroy();
	dir_ = dir;
	name_ = file_name;
	std::string	szFileFath;
	szFileFath += dir;                    //CSV文件所在路径
	szFileFath += file_name;
    FILE* file_stream = fopen(szFileFath.c_str(),"rb");
	if ( file_stream)
	{	
		int32_t size = 0;
		fseek(file_stream,0L,SEEK_END);
		size = ftell(file_stream);
		fseek(file_stream,0L,SEEK_SET);
		if (size != 0)
		{
			char* buf = new char[size + 1];
			buf[size] = '\0';
			
			if (buf == NULL)
			{
				return false;
			}
			
			fread(buf,sizeof(char),size,file_stream);
			fclose(file_stream);
			file_stream = NULL;
            char* out_buf = NULL;
            if (!check_utf8_and_get_data(buf,out_buf))
            {
                MF_ERROR("csv name = %s,file format is not utf8!\n",file_name.c_str());
                delete buf;
                ACE_ASSERT(false);
                return false;
            }
			
			std::vector<std::string> line_string;
			data_row_count_  = _split_string(out_buf,line_string,"\r\n",true,true);
            delete buf;
			// 第一行为中文说明，第二行为键，第三行为字段类型
			data_row_count_ -= 3;

			if (data_row_count_ <= 0)
			{
				 MF_ERROR("csv data_row_count_ <= 0 \n");
                 fclose(file_stream);
				 return false;
			}
			
			std::vector<std::string>::iterator it = line_string.begin();
			// 第一行为中文说明略去
			

			// 第二行为键
			++it;
			data_col_count_  = _split_string(*it,data_Field_name_map_,separator_[CSV_SEPARTOR_COMMA],false,false);	
			if (data_row_count_ <= 0)
			{
				 MF_ERROR("csv data_col_count_ <= 0 \n");
				return false;
			}

			// 第三行为数据类型
			++it;
			int32_t count = _parse_field_type(*it,data_field_type_vec_,separator_[CSV_SEPARTOR_COMMA],false,false);	
			if (count != data_col_count_)
			{
				MF_ERROR("csv data_col_count_ err \n");
				return false;
			}
			
			
			// 其余行为数据
			++it;
			for ( int32_t i = 0; i < data_row_count_; ++i,++it )
			{
				Csv_Row* row = _creat_row();
				ACE_ASSERT(row != NULL);
				if (row)
				{
					count = _parse_row_data(*it,*row,separator_[CSV_SEPARTOR_COMMA]);
					ACE_ASSERT(count == data_col_count_);
					if (count != data_col_count_)
					{
						MF_ERROR("csv data_col_count_ err \n");
						return false;
					}
					add_new_row(row);
				}
				else
				{
					MF_ERROR("create Csv_Row = null \n");
				}
			}
			
		}
		return true;
		
	}
	return false;
}
//-----------------------------------------------------------------------------
bool Csv_Reader::create( char* memory, int32_t size, const std::string& file_path )
{
	return false;
}
//-----------------------------------------------------------------------------
bool Csv_Reader::save_to_file( const std::string& filename, char* memory, int32_t size )
{
	return false;
}
//-----------------------------------------------------------------------------
bool Csv_Reader::save_to_file(const std::string& filename)
{
	return false;
}
//-----------------------------------------------------------------------------
void Csv_Reader::destroy()
{
	Csv_Row_Iter row_it = data_table_vec_.begin();
	for (; row_it != data_table_vec_.end(); ++row_it)
	{
		Csv_Row* row = *row_it;
		if (row)
		{
			_destory_row(row);
		}
		else
		{
			ACE_ASSERT(false);
			continue;
		}
	}
	data_table_vec_.clear();

	
	
}
//-----------------------------------------------------------------------------
void Csv_Reader::set_type( CSV_SEPARTOR_TYPE type )
{
	separator_type_ = type;
}
//-----------------------------------------------------------------------------
Csv_Reader::CSV_SEPARTOR_TYPE Csv_Reader::get_type()
{
	return separator_type_;
}

//-----------------------------------------------------------------------------
Csv_Reader::Csv_Row* Csv_Reader::find_row( int32_t sequence )
{
	if (sequence >= 0 && sequence < data_row_count_)
	{
		return data_table_vec_[sequence];
	}
	return NULL;
}


Csv_Reader::Csv_Field* Csv_Reader::find_field( Csv_Row* row, const std::string& field_name )
{
	int32_t index = get_field_sequence(field_name);
	if (index >= 0 && index != INDEX_ERR)
	{
		return (*row)[index];
	}
	return NULL;
}

Csv_Reader::Csv_Field* Csv_Reader::find_field(Csv_Row* row, int32_t field_seq)
{
	if (field_seq >= 0 && field_seq < data_col_count_)
	{
		return (*row)[field_seq];
	}
	return NULL;
}

//-----------------------------------------------------------------------------
bool Csv_Reader::get_field_name( int32_t index,std::string& field_name )
{
	if (index < 0 && index >= data_col_count_)
	{
		return false;
	}

	Field_Seq_Iter it = data_Field_name_map_.left.find(index);
	Field_Seq_Iter itEnd = data_Field_name_map_.left.end();
	if (it != itEnd)
	{
		field_name = it->second;
		return true;
	}
	
	return false;
}
//-----------------------------------------------------------------------------
int32_t Csv_Reader::get_field_sequence( const std::string& col_key )
{
	int32_t ret = INDEX_ERR;
	Field_Name_Iter it = data_Field_name_map_.right.find(col_key);
	Field_Name_Iter itEnd = data_Field_name_map_.right.end();
	if (it != itEnd)
	{
		ret = it->second; 
	}
	return ret;
}

//-----------------------------------------------------------------------------
void Csv_Reader::add_new_row(  Csv_Row* row )
{
	ACE_ASSERT(row);
	data_table_vec_.push_back(row);
}

//-----------------------------------------------------------------------------
int32_t Csv_Reader::_split_string( const std::string& src_string, std::vector<std::string>& dest_str, const std::string& separator_format, bool is_one_key, bool is_ignore_empty )
{
	dest_str.clear();
	if(src_string.empty())
	{
		return 0;
	}

	std::string::size_type left = 0;
	std::string::size_type right;
	if(is_one_key)
	{
		right = src_string.find_first_of(separator_format);
	}
	else
	{
		right = src_string.find(separator_format);
	}

	if(right == std::string::npos)
	{
		right = src_string.length();
	}
	while(true)
	{
		std::string strItem = src_string.substr(left, right-left);
		if(strItem.length() > 0 || !is_ignore_empty)
		{
			dest_str.push_back(strItem);
		}

		if(right == src_string.length())
		{
			break;
		}

		left = right + (is_one_key ? 1 : separator_format.size());

		if(is_one_key)
		{
			std::string strTemp = src_string.substr(left);
			right = strTemp.find_first_of(separator_format);
			if(right != std::string::npos) right += left;
		}
		else
		{
			right = src_string.find(separator_format, left);
		}

		if(right == std::string::npos)
		{
			right = src_string.length();
		}
	}

	return (int32_t)dest_str.size();
}
//-----------------------------------------------------------------------------
int32_t Csv_Reader::_split_string( const std::string& src_string, Data_Field_Name_Map& dest_map, const std::string& separator_format,bool is_one_key, bool is_ignore_empty )
{
	dest_map.clear();
	if(src_string.empty())
	{
		return 0;
	}

	std::string::size_type left = 0;
	std::string::size_type right;
	if(is_one_key)
	{
		right = src_string.find_first_of(separator_format);
	}
	else
	{
		right = src_string.find(separator_format);
	}

	if(right == std::string::npos)
	{
		right = src_string.length();
	}

	int32_t col_index = 0;
	while(true)
	{
		std::string str_item = src_string.substr(left, right-left);
		if(str_item.length() > 0 || !is_ignore_empty)
		{
			dest_map.insert(Data_Field_Name_Map::value_type(col_index,str_item));
		}

		if(right == src_string.length())
		{
			break;
		}

		left = right + (is_one_key ? 1 : separator_format.size());

		if(is_one_key)
		{
			std::string strTemp = src_string.substr(left);
			right = strTemp.find_first_of(separator_format);
			if(right != std::string::npos) right += left;
		}
		else
		{
			right = src_string.find(separator_format, left);
		}

		if(right == std::string::npos)
		{
			right = src_string.length();
		}
		++col_index;
	}

	return (int32_t)dest_map.size();
}
//-----------------------------------------------------------------------------
int32_t Csv_Reader::_parse_field_type( const std::string& src_string, std::vector< CSV_FIELD_TYPE >& field_types, const std::string& separator_format, bool is_one_key, bool is_ignore_empty )
{
	std::vector<std::string> strings;
	int32_t count = _split_string(src_string,strings,separator_format,false,false);

	for (std::vector<std::string>::iterator it = strings.begin(); it != strings.end(); ++it)
	{
        bool has_type = false;
		for (int32_t i = CSV_FIELD_TYPE_FLOAT; i < CSV_FIELD_TYPE_MAX; ++i)
		{
			if ((*it).compare(field_type_text[i]) == 0)
			{
				data_field_type_vec_.push_back((CSV_FIELD_TYPE)i) ;
                has_type = true;
			}
            
        }
        if (!has_type)
        {
            MF_ERROR("csv name = %s key type = %s error\n!",name_.c_str(),(*it).c_str());
            ACE_ASSERT(false);
        }
	}
	
	//解析路径
	std::vector< CSV_FIELD_TYPE >::iterator type_iter = data_field_type_vec_.begin();
	int32_t seq = 0;
	std::string field_dir,temp;
	bool has_path = false;
	for (; type_iter != data_field_type_vec_.end(); ++type_iter,++seq)
	{
		has_path = false;
		field_dir = "";
		switch(*type_iter)
		{
		case CSV_FIELD_TYPE_FLOAT:
		case CSV_FIELD_TYPE_INT:
		case CSV_FIELD_TYPE_STRING:
			break;
		case CSV_FIELD_TYPE_TEXT:
		case CSV_FIELD_TYPE_BIN:
			has_path = true;
			field_dir += dir_;
			dir_ += "/";
			get_field_name(seq,temp);
			field_dir += temp;
			field_dir += "/";
			break;
		default:
			ACE_ASSERT(false);
		}
		if (has_path)
		{
			data_field_dir_map_[seq] = field_dir;
		}
	}
	return count;
}
//-----------------------------------------------------------------------------
int32_t Csv_Reader::_parse_row_data( const std::string& src_string, Csv_Row& row, const std::string& separator_format )
{
	std::vector<std::string> record;
	int line_pos = 0;
	int inquotes = false;
	char c;
	int length = src_string.length();
	string cur_string;
	while( src_string[line_pos]!= 0 && line_pos < length )
	{
		c = src_string[line_pos];
		if (!inquotes && cur_string.length() == 0 && c == '"')
		{
			//beginquotechar
			inquotes = true;
		}
		else if ( inquotes && c == '"')
		{
			//quotechar
			if ( (line_pos+1 <length) && (src_string[line_pos+1] == '"') ) 
			{
				//encountered 2 double quotes in a row (resolves to 1 double quote)
				cur_string.push_back(c);
				line_pos++;
			}
			else
			{
				//endquotechar
				inquotes = false; 
			}
		}
		else if ( !inquotes && (c == *separator_format.c_str()))
		{
			//end of field
			record.push_back( cur_string );
			cur_string = "";
		}
		else if ( !inquotes && (c == '\r' || c == '\n') )
		{
			record.push_back( cur_string );
			break;
		}
		else
		{
			cur_string.push_back(c);
		}
		line_pos++;
	}

	record.push_back( cur_string );

	int seq = 0;
	std::vector<std::string>::iterator record_it = record.begin();
	for (; record_it != record.end(); ++record_it,++seq)
	{
		std::string& record = *record_it;
		switch(data_field_type_vec_[seq])
		{
		case CSV_FIELD_TYPE_FLOAT:
			row[seq]->field_value->double_value = ACE_OS::atof(record.c_str());
			break;
		case CSV_FIELD_TYPE_INT:
			row[seq]->field_value->long64_value = ACE_OS::atol(record.c_str());
			break;
		case CSV_FIELD_TYPE_BIN:
			if (!record.empty())
			{
				_read_bin_file(data_field_dir_map_[seq] + record,row[seq]->field_value->bin_data.bin_data,row[seq]->field_value->bin_data.data_size);
			}
			break;
		case CSV_FIELD_TYPE_STRING:
			if (record.empty())
			{
				row[seq]->field_value->text[0] = 0;
			}
			else
			{
				if (record.size() > MAX_STRING_DATA_SIZE )
				{
// 					std::string err = "File:",temp;
// 					err+=	name_;
// 					err += "Fild:";
// 					get_field_name(seq,temp);
// 					err += temp;
//					err += "too large size >= 5k \n";
					MF_ERROR("csv string too large size > 5k \n");
					return seq;
				}
				memcpy(row[seq]->field_value->text,record.c_str(),record.size());
				row[seq]->field_value->text[record.size()] = 0;
			}
			break;
		case CSV_FIELD_TYPE_TEXT:
			_read_text_file(data_field_dir_map_[seq] + record,row[seq]->field_value->text);
			break;
		default:
			ACE_ASSERT(0);
			MF_ERROR("Csv_Field  err \n");
			break;
		}
	}

	return seq;

}
//-----------------------------------------------------------------------------
Csv_Reader::Csv_Row* Csv_Reader::_creat_row()
{
	Csv_Row* row = NULL;
	if (data_field_type_vec_.empty())
	{
		return	row;
	}

	row = new Csv_Row();
	std::vector< CSV_FIELD_TYPE >::iterator it = data_field_type_vec_.begin();
	for (; it != data_field_type_vec_.end(); ++it)
	{
		Csv_Field* field = new Csv_Field(*it);
		row->push_back(field);
	}

	return row;
}

//-----------------------------------------------------------------------------
void Csv_Reader::_destory_row( Csv_Row* row )
{
	if (row)
	{
		Csv_Field_Iter field_iter = row->begin();
		for (; field_iter != row->end(); ++field_iter )
		{
			Csv_Field* field = *field_iter;
			if (field)
			{
				delete field;
				field = NULL;
			}
			else
			{
				continue;		
			}
		}
		row->clear();
		delete row;
	}
	
}
//-----------------------------------------------------------------------------
bool Csv_Reader::_read_text_file( const std::string& file_name, char* buff)
{
	bool ret = false;
     FILE * file_stream = fopen(file_name.c_str(),"rb");
	if (file_stream)
	{
		int32_t size = 0;
		fseek(file_stream,0L,SEEK_END);
		size = ftell(file_stream);
		fseek(file_stream,0L,SEEK_SET);
		if (size != 0)
		{
			if (size >= MAX_TEXT_DATA_SIZE)
			{
				// 				std::string err = "File:";
				// 				err +=	name_;
				// 				err +=	"Field file";
				// 				err += file_name;
				// 				err += "too large size >= 20k \n";
				MF_ERROR("text file too large size >= 20k \n");
                fclose(file_stream);
				return ret;
			}
			buff[size] = 0; 
			fread(buff,sizeof(char),size,file_stream);
            char* out_buf = NULL;
            if (!check_utf8_and_get_data(buff,out_buf))
            {
                MF_ERROR("text name = %s,file format is not utf8!\n",file_name.c_str());
                ACE_ASSERT(false);
                return false;
            }
            //去掉bom
            if (buff + 3 == out_buf)
            {
                memmove(buff,out_buf,size - 3);
                buff[size - 3] = 0;
            }
			ret = true;
		}

		fclose(file_stream);
		file_stream = NULL;
	}
	return ret;
}


bool Csv_Reader::_read_bin_file( const std::string& file_name, char* buff, int32_t& buff_size )
{
	bool ret = false;
    FILE * file_stream = fopen(file_name.c_str(),"rb");
	if (file_stream)
	{
		int32_t size = 0;
		fseek(file_stream,0L,SEEK_END);
		size = ftell(file_stream);
		fseek(file_stream,0L,SEEK_SET);
		
		if (size != 0)
		{
			if (size >= MAX_BIN_DATA_SIZE)
			{
				// 				std::string err = "File:";
				// 				err +=	name_;
				// 				err +=	"Field file";
				// 				err += file_name;
				// 				err += "too large size >= 30k \n";
				MF_ERROR("bin file too large size >= 30k \n");
                fclose(file_stream);
				return ret;
			}
			buff[size] = 0; 
			fread(buff,sizeof(char),size,file_stream);
			buff_size = size;
            char* out_buf = NULL;
            if (!check_utf8_and_get_data(buff,out_buf))
            {
                MF_ERROR("bin file name = %s,file format is not utf8!\n",file_name.c_str());
                ACE_ASSERT(false);
                return false;
            }
            // 去掉bom
            if (buff + 3 == out_buf)
            {
                memmove(buff,out_buf,size - 3);
                buff_size -= 3;
                buff[buff_size] = 0;
            }
			ret = true;
		}

		fclose(file_stream);
		file_stream = NULL;
	}
	return ret;
}

bool Csv_Reader::check_utf8_and_get_data( char* _in_buff,char*& _out_buff )
{
    // 检查bom  EF、BB、BF utf8
    if ((uint8_t)_in_buff[0] == 0xEF && (uint8_t)_in_buff[1] ==  0xBB && (uint8_t)_in_buff[2] == 0xBF)
    {
        _out_buff = _in_buff += 3;
        return true;
    }
    // FF、FE unicode _in_buff[0] == 0xEF && _in_buff[1] == 0xFF
    if (((uint8_t)_in_buff[0] == 0xFF && (uint8_t)_in_buff[1] == 0xFE)
        || ((uint8_t)_in_buff[0] == 0xFE && (uint8_t)_in_buff[1] == 0xFF))
    {
        return false;
    }
    
    // 只能区分头，不能区分内容的编码
    _out_buff = _in_buff;
    return true;
    
}