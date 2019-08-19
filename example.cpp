#include "pushcpp.h"
#include "pusher.h"
using namespace std;

int WINAPI WinMain
(
	HINSTANCE hInstance,		// ���������� �������� ���������� ����
	HINSTANCE hPrevInstance,		// ���������� ����������� ���������� ���� 
	LPSTR lpCmdLine,			// ��������� �� ��������� ������
	int nCmdShow 			// ���������� ��������� ���� 
) {
	WSADATA wsadata;
	WSAStartup(MAKEWORD(1,1),&wsadata);
	pusher pp("192.168.1.168:6001/app/key", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/75.0.3770.142 Safari/537.36");
	pp.connect();
	pp.subscribe("private-user.1", "192.168.1.168", 81, "broadcasting/auth", "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjFiNDA2ZjY0ZTMwNWM3OTI5ODJmYTgxNTk5YzZmZjlhZGI1MzkwMGYwM2EyM2FjMDE3Y2YxNGMwNGE4MzM1MTM5NDRjYTVkYmJhOWFiMTc4In0.eyJhdWQiOiIxIiwianRpIjoiMWI0MDZmNjRlMzA1Yzc5Mjk4MmZhODE1OTljNmZmOWFkYjUzOTAwZjAzYTIzYWMwMTdjZjE0YzA0YTgzMzUxMzk0NGNhNWRiYmE5YWIxNzgiLCJpYXQiOjE1NjQwNTU0MDgsIm5iZiI6MTU2NDA1NTQwOCwiZXhwIjoxNTk1Njc3ODA4LCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.CTDMrSCqpEVWMCyFNBSyQbE_QSRvh8CDO0aBId11pBNWG9jozM9xCyaC3Bdb4LLp6VOVdi_8DeKx4HMcdSy6gwAV10gMfOOJOyixReSH9FOHYorJApzFcQS5xaWgFbh8v7RzxL68ImouSISkxr5yvCnixYDS9nKvG4hX1Dy7vOqJ7aFqBM7iPtfXvFO6TnSxnIMDPEYGbElaqdZ25vH5ZuWS0hpYr5hWaFcrjTZ8Um1inL_9AbJXO2RYcV-PY72VNPFAfOy1GTJvI-WQVmdiLKmd35dWvCNky5C5sw4baVwgRrWeY4Tjt8AG6SExnUj-TaeWiu7hzjxXkZzjKLc9Z9yQbtthQvgozfXjEkgc-e8sipVdhkZQC93FjLHRZIBPUKMDVX2NrmjfVBL3FJvjbW2-x6nozXvTQnT4gU1BhB_eZrQhZ4s6cS_UN-9gS3PQLwJmWjY0JlKCKNk2NY4uhWvBnhpJRb2JaLYa7Dk4sIoLwGpiTPc9kp2X4c9WgBfx0BuViL0ZXv3K37j3VQoUcU3fAAXV9RFovb8SGO6oPIuq5XZL-VUbWcDM4PajXpR0bqiaCgmmhw4c0ZR5QpHgrRMQhotpu6SaY3FmQlM2LRwtPzV0IuNxMEcoQhD_i4yEA25ZSq7a25T2jr0lukyH_S1nsVo_rsEIhdZlDlzHSEw");
	//pp.subscribe("private-user.2", "192.168.1.168", 81, "broadcasting/auth", "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6ImY2ZGFkZWM5MTdmMTM2Mzc3NDA0ZTQyMmFiMjVkOWU4Y2Q2NjE0Mjc5MDY5ZDFhNmRiOTE1NTk1YmFiOGZjMWI1YmQwZTQ4Njc0ZDE4ZTg3In0.eyJhdWQiOiIyIiwianRpIjoiZjZkYWRlYzkxN2YxMzYzNzc0MDRlNDIyYWIyNWQ5ZThjZDY2MTQyNzkwNjlkMWE2ZGI5MTU1OTViYWI4ZmMxYjViZDBlNDg2NzRkMThlODciLCJpYXQiOjE1NjU3NzU2MTUsIm5iZiI6MTU2NTc3NTYxNSwiZXhwIjoxNTk3Mzk4MDE1LCJzdWIiOiIxMjEwIiwic2NvcGVzIjpbXX0.SEK8A1jO4xOInVwiYFxPatEckTYoZSUv_bERGZNbEscv_P-PAywsLmMCNz5KSw6f2r5DtaVynDjZse_k94wMr_6pGkivuMwn9KvjhfMAKMh35GrtTRtvtiisSTMLj9hUh8y5j-vpHnWcQz_i4crZo4BspRwXflm1W4U2s5mTJfGUjy_Yx9ofU1BDoCKoVrdRgNEQzbKAgE_p9f1Yd3EawT9zkxxguYFwROlKmSBmjYaQXhrgKJmsGBDH8e2AQobyBLZkSDIZhIZgM1cPtHVbmbZuUyng0TXe1q4EO3LR2NmfTmuFDZPy1URdaQ3Pr3xzDiGMNrQj94FSOgfpXwzPjp1LcySFz4d-KTEdeB1ZEwsJrDALp9eq_kAIlIjUwemzsQ0A8EbLTsHiajVI8w1viCq0fRzpfwfUpTArsrkpkP2iXSDK32zUwo_4F4dwSkpwf9ElJEaNCaNExppS3o-Car7T_OjewKYKKEL1GQqhX0SfHwCEX07ZAEhaYYDBoixZqDCckhekCo0C8IsfexRvTAv7oOD4wCnvhks7e2ctH3_S7wtxsmjkEBoFOsWS_h0KHIYoLF0iijjc-iLVeOZyuygvBhMgXArFGqis2lGAllUStue4bkPiDxcfNcNkkkebWqDh5ll89KLhiKuosSaU6l7mTy26iStjnXmiD4iMQCY");
	pp.join();
	return WSACleanup();
}
