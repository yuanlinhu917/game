
/*****************************************************************
* Copyright (c)2009，上海美峰数码科技有限公司
* All rights reserved.
* 
* 文件名称：Csv_Reader.h
* 文件标识：
* 摘    要：
* 
* 当前版本：1.0
* 作    者：王育安
* 完成日期：2013-11-7
*
******************************************************************/

/******************************************************************************/
#ifndef _CSVREADER_H_
#define _CSVREADER_H_
/******************************************************************************/
#include "Define.h"
#include  "boost/bimap.hpp" 
#include "ace/Assert.h"

#define MAX_BIN_DATA_SIZE 1024 * 60		//30k
#define MAX_TEXT_DATA_SIZE 1024 * 40	//20k
#define MAX_STRING_DATA_SIZE 1024 * 10 	//5k

/******************************************************************************/
//CSV 文件读取
/******************************************************************************/
class Csv_Reader
{

public:
	// 错误返回值
	enum ERR
	{
		INDEX_ERR = -1
	};
	
	//分隔符类型
	enum CSV_SEPARTOR_TYPE
	{
		CSV_SEPARTOR_COMMA = 0,
		CSV_SEPARTOR_TAB,
		CSV_SEPARTOR_ENCODE,
		CSV_SEPARTOR_MAX
	};
	
	//字段类型
	enum CSV_FIELD_TYPE 
	{
		CSV_FIELD_TYPE_FLOAT = 0,
		CSV_FIELD_TYPE_INT,
		CSV_FIELD_TYPE_BIN,
		CSV_FIELD_TYPE_STRING,
		CSV_FIELD_TYPE_TEXT,
		CSV_FIELD_TYPE_MAX,
	};


	//二进制数据
	struct Bin_Data
	{
		int32_t data_size;
		char*	bin_data;
	};

	// 字段内容
	union Csv_Field_Value
	{
		friend class Csv_Field;
		friend class Csv_Reader;
	private:
		double		double_value;
		int64_t		long64_value;
		Bin_Data	bin_data;
		char		*text;
	};

	// 字段信息
	class Csv_Field
	{
		friend class Csv_Reader;
	public:
		bool		get_double(double& float_value);
		bool		get_int64(int64_t& int_value);
		bool		get_string(char* string_data);
		bool		get_bin(char* bin_data,int32_t&size);

		bool		to_float(float& flt_val);
		bool		to_double(double& flt_val);
		bool		to_int8(int8_t& int_val);
		bool		to_uint8(uint8_t& int_val);
		bool		to_int16(int16_t& int_val);
		bool		to_uint16(uint16_t& int_val);
		bool		to_int32(int32_t& int_val);
		bool		to_uint32(uint32_t& int_val);
		bool		to_int64(int64_t& int_val);
		bool		to_uint64(uint64_t& int_val);
		bool		text_to_string(std::string& str_val);
		bool		bin_to_string(std::string& bin_val);

		~Csv_Field();
	private:
		Csv_Field_Value* field_value;
		CSV_FIELD_TYPE   field_type;

		Csv_Field();
		Csv_Field(CSV_FIELD_TYPE type);
	};

	
	
public:

	typedef std::vector< Csv_Field* >::iterator								Csv_Field_Iter;
	typedef std::vector< Csv_Field* >										Csv_Row;

	typedef	std::vector< Csv_Row* >::iterator								Csv_Row_Iter;
	typedef	std::vector< Csv_Row* >											Csv_Table;

	typedef	boost::bimaps::bimap< int, std::string >::left_map::iterator	Field_Seq_Iter;
	typedef	boost::bimaps::bimap< int, std::string >::right_map::iterator	Field_Name_Iter;
	typedef	boost::bimaps::bimap< int, std::string >						Data_Field_Name_Map;


	
public:
	Csv_Reader();
	~Csv_Reader();

public:
	bool				create( const std::string& dir, const std::string& file_name);									//Open csv by filename
	bool				create(char* memory, int32_t size, const std::string& file_path);								//Open csv by memory
	void				destroy();	

	bool				save_to_file(const std::string& file_name, char* memory, int32_t size);							//Save the file memory to file
	bool				save_to_file(const std::string& file_name);

	void			  	set_type(CSV_SEPARTOR_TYPE type);																//Set the sperator value, default is comma ','
	CSV_SEPARTOR_TYPE 	get_type();																						//Get the current sperator use

	Csv_Row*			find_row(int32_t sequence);																		//Find value by row's sequence. Return the row of csv by row number.
	Csv_Field*			find_field(Csv_Row* row, const std::string& field_name);
	Csv_Field*			find_field(Csv_Row* row, int32_t field_seq);

	bool				get_field_name(int32_t sequence, std::string& field_key);										//Get column key name by col sequence
	int32_t				get_field_sequence(const std::string& field_key);												//Get column sequence name by field key
	
	int32_t				field_count(){return (int32_t)(data_row_count_ * data_col_count_);}								//Total record in csv
	int32_t				get_col_count(){return data_col_count_;}
	int32_t				get_row_count(){return data_row_count_;}

	void				add_new_row(Csv_Row* row);

    bool                check_utf8_and_get_data(char* in_buff,char*& out_buff);
private:

	int32_t			_split_string( const std::string& src_string, 
		std::vector<std::string>& dest_str,
		const std::string& separator_format,
		bool is_one_key,
		bool is_ignore_empty);

	int32_t			_split_string( const std::string& src_string, 
		Data_Field_Name_Map& dest_map,
		const std::string& separator_format,
		bool is_one_key,
		bool is_ignore_empty);

	int32_t			_parse_field_type( const std::string& src_string,
		std::vector< CSV_FIELD_TYPE >& field_type,
		const std::string& separator_format,
		bool is_one_key,
		bool is_ignore_empty);

	int32_t			_parse_row_data( const std::string& src_string,
		Csv_Row& row,
		const std::string& separator_format);

	Csv_Row*		_creat_row();
	void			_destory_row(Csv_Row* row);

	bool			_read_text_file( const std::string& file_name, char* buff);
	bool			_read_bin_file( const std::string& file_name, char* buff, int32_t& buff_size );

private:

	Csv_Table								data_table_vec_;
	Data_Field_Name_Map						data_Field_name_map_;

	//字段类型
	std::vector< CSV_FIELD_TYPE >			data_field_type_vec_;
	//特殊字段路径
	std::map< int32_t,std::string >			data_field_dir_map_;
	//配置信息	
	std::string								field_type_text[CSV_FIELD_TYPE_MAX];						

	int32_t									data_col_count_;
	int32_t									data_row_count_;

	//分隔符配置信息
	CSV_SEPARTOR_TYPE						separator_type_;
	std::string								separator_[CSV_SEPARTOR_MAX];

	std::string								dir_;
	std::string								name_;
	
};



#endif