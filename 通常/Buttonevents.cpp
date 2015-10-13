# include "ButtonEvents.h"
# include "Class.h"
# include "MainFunc.h"
# include <boost/asio.hpp>
# include <string>
# include <fstream>

using namespace std;
using namespace boost;

string FilePass;
string HOST;
string token;
int quest;
extern GUIout Gout;

//�ݒ�̓ǂݍ���
void LoadConfig() {
	string str;
	ifstream ifs("files/config.txt");
	ifs >> HOST;
	HOST = HOST.substr(string("HOST:").length());
	ifs >> token;
	token = token.substr(string("token:").length());
	ifs >> str;
	str = str.substr(string("quest:").length());
	quest = atoi(str.c_str());
	ifs.close();
}

//�_�E�����[�h���Ď��s
void download(bool* end){
	try {
		asio::io_service io;
		//TCP�\�P�b�g�쐬
		asio::ip::tcp::socket socket(io);
		//���O����
		asio::ip::tcp::resolver resolver(io);
		asio::ip::tcp::resolver::query query(HOST, "http");
		Gout << L"�ڑ����Ă��܂�...";
		//�z�X�g����ݒ�
		asio::ip::tcp::endpoint endpoint(*resolver.resolve(query));
		//�\�P�b�g�֐ڑ�
		socket.connect(endpoint);
		Gout << L"����\n";
		//���N�G�X�g���M
		Gout << L"HTTP���N�G�X�g�𑗐M...";
		//GET
		asio::streambuf request;
		ostream request_stream(&request);
		request_stream << "GET /quest" << quest << ".txt?token=" << token << " HTTP/1.0\r\n";
		request_stream << "Host: " << HOST << "\r\n\r\n";
		asio::write(socket, request);
		Gout << L"����\n";
		//��M
		asio::streambuf response;
		system::error_code ec;
		asio::read(socket, response, asio::transfer_all(), ec);
		Gout << L"�_�E�����[�h����\n";
		//�o��
		string buff;
		istream response_stream(&response);
		ofstream ofs("files/quest.txt");

		do {
			getline(response_stream, buff);
		} while (buff != "\r");
		while (getline(response_stream, buff)) {//�{��
			buff.erase(--buff.end());
			ofs << buff << endl;
		}
		ofs.close();
		Gout << L"�ۑ�����\n";
		FilePass = "files/quest.txt";
		MainFunc("files/quest.txt");
	}
	catch (std::exception& e) {
		Gout << Widen(e.what());
		Gout << L"\n";
	}
	*end = true;
	
}

//�t�@�C����I�����Ď��s
void selectfile(bool* end){
	//�t�@�C���I��
	if (const auto folder = Dialog::GetOpen({ { L"���t�@�C�� (*.txt)", L"*.txt" } })){
		FilePass = folder.value().narrow();
		MainFunc((char*)folder.value().narrow().c_str());
	}
	*end = true;
}

//�A�b�v���[�h
void upload(bool* end){
	try {
		asio::io_service io;
		//TCP�\�P�b�g�쐬
		asio::ip::tcp::socket socket(io);
		//���O����
		asio::ip::tcp::resolver resolver(io);
		asio::ip::tcp::resolver::query query(HOST, "http");
		Gout << L"�ڑ����Ă��܂�...";
		//�z�X�g����ݒ�
		asio::ip::tcp::endpoint endpoint(*resolver.resolve(query));
		//�\�P�b�g�֐ڑ�
		socket.connect(endpoint);
		Gout << L"����\n";

		//���N�G�X�g���M
		Gout << L"���M��...";
		//POST
		string boundary = "----102852708831426";
		string result;
		string buffer;
		ifstream ifs("files/result.txt");
		while (getline(ifs, buffer)) {
			result += buffer + "\r\n";
		}
		string data;
		data += "--" + boundary + "\r\n";
		data += "Content-Disposition: form-data; name=\"token\"\r\n";
		data += "\r\n";
		data += token + "\r\n";
		data += "--" + boundary + "\r\n";
		data += "Content-Disposition: form-data; name=\"answer\"; filename=\"result.txt\"\r\n";
		data += "Content-Type: text/plain\r\n";
		data += "\r\n";
		data += result;
		data += "\r\n";
		data += "--" + boundary + "--\r\n";
		data += "\r\n";

		asio::streambuf request;
		ostream request_stream(&request);
		request_stream << "POST /answer HTTP/1.0\r\n";
		request_stream << "Host: " << HOST << "\r\n";
		request_stream << "Content-Type: multipart/form-data; boundary=" << boundary << "\r\n";
		request_stream << "Content-Length: " << data.length() << "\r\n";
		request_stream << "\r\n";
		request_stream << data;
		asio::write(socket, request);

		//��M
		asio::streambuf response;
		system::error_code ec;
		asio::read(socket, response, asio::transfer_all(), ec);
		Gout << L"����\n";
		//�o��
		istream response_stream(&response);
		for (int i = 0; i < 8; i++) {
			getline(response_stream, buffer);
		}
		while (getline(response_stream, buffer)) {
			Gout << Widen(buffer.c_str()) + L"\n";
		}
	}
	catch (std::exception& e) {
		Gout << Widen(e.what());
		Gout << L"\n";
	}
	*end = true;
}

//���������Ȃ���
void reanswer(bool* end) {
	MainFunc((char*)FilePass.c_str());
	*end = true;
}