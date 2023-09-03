#include<thread>
#include<iostream>
#include<string>
#include<vector>
#include<chrono>
#include<execution>

using namespace std;
using namespace chrono;
static const char base16[] = "0123456789abcdef";
void Base16Encode(const unsigned char* data, int size, unsigned char* out) {
	for (int i = 0; i < size; i++) {
		unsigned char d = data[i];
		//0000 0000
		//1234 5678 >>4 0000 1234
		//1234 5678 & 0000 1111   0000 5678
		char a = base16[d >> 4];
		char b = base16[d & 0x0f];
		//ʹ��out������λ�÷ֱ�洢��λ�͵�λ
		out[i * 2] = a;
		out[i * 2 + 1] = b;
	}
}
//C++11 ���base16����
void Base16EncodeThread(const vector<unsigned char>& data, vector<unsigned char>& out) {
	int size = data.size();
	int th_count = thread::hardware_concurrency();//ϵͳ֧�ֵ��̺߳�����
	//��Ƭ����
	int slice_count = size / th_count;//����������
	if (size < th_count) {//ֻ��һƬ
		th_count = 1;
		slice_count = size;
	}
	//׼�����߳�
	vector<thread>ths;
	ths.resize(th_count);
	
	//������䵽�����߳� 1234 5678 9acb defg
	for (int i = 0; i < th_count; i++) {
		int offset = i * slice_count;
		int count = slice_count;

		//���һ�������ǲ�ȫ��
		if (th_count > 1 && i == th_count - 1) {
			count = slice_count + size % th_count;
		}
		cout << offset << ": " << count << endl;
		ths[i] = thread(Base16Encode, data.data() + offset, count, out.data());
	}
	//�ȴ������̴߳������
	for (auto& th : ths) {
		th.join();
	}
}

int main(int argc, char* argv[]) {

	string test_data = "����base16����";
	unsigned char out[1024] = { 0 };
	Base16Encode((unsigned char*)test_data.data(), test_data.size(), out);
	cout << "base16:" << out << endl;

	//��ʼ����������
	vector<unsigned char>in_data;
	in_data.resize(1024*1024*10);//10M
	//in_data.data();
	for (int i = 0; i < in_data.size(); i++) {
		in_data[i] = i % 256;
	}
	vector<unsigned char>out_data;
	out_data.resize(in_data.size() * 2);

	//���Ե��߳�base16����Ч��
	{
		cout << "���߳�base16���� ��ʼ����" << endl;
		auto start = system_clock::now();
		Base16Encode(in_data.data(), in_data.size(), out_data.data());
		auto end = system_clock::now();
		auto duration = duration_cast<milliseconds>(end - start);
		cout << "����" << in_data.size() << "�ֽ����ݻ���" << duration.count() << "ms" << endl;
		//cout << out_data.data() << endl;
	}

	//����c++11 ���Զ��߳�Base16����
	{
		cout << "C++ ���߳�Base16���� ��ʼ����" << endl;
		auto start = system_clock::now();
		Base16EncodeThread(in_data,out_data);
		auto end = system_clock::now();
		auto duration = duration_cast<milliseconds>(end - start);
		cout << "����" << in_data.size() << "�ֽ����ݻ���" << duration.count() << "ms" << endl;
		//cout << out_data.data() << endl;
	}
	//����C++17 ���߳�base16����
	{
		cout << "C++17 ���߳�Base16���� ��ʼ����" << endl;
		auto start = system_clock::now();
		unsigned char* idata = in_data.data();
		unsigned char* odata = out_data.data();
		std::for_each(std::execution::par,//���м��� ���
			in_data.begin(), in_data.end(),
			[&](auto& d) {//���߳̽���˺���
				char a = base16[d >> 4];
				char b = base16[d & 0x0f];
				int index = &d - idata;
				odata[index * 2] = a;
				odata[index * 2 + 1] = b;
			}
		);

		auto end = system_clock::now();
		auto duration = duration_cast<milliseconds>(end - start);
		cout << "����" << in_data.size() << "�ֽ����ݻ���" << duration.count() << "ms" << endl;
		//cout << out_data.data() << endl;
	}

	getchar();
	return 0;
}