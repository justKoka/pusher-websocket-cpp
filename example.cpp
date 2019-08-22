#include "pushcpp.h"
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
	pushcpp pp("192.168.1.168:6001/app/key", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/75.0.3770.142 Safari/537.36");
	pp.connect();
	pp.subscribe("private-user.1", "192.168.1.168", 81, "broadcasting/auth", "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjFiNDA2ZjY0ZTMwNWM3OTI5ODJmYTgxNTk5YzZmZjlhZGI1MzkwMGYwM2EyM2FjMDE3Y2YxNGMwNGE4MzM1MTM5NDRjYTVkYmJhOWFiMTc4In0.eyJhdWQiOiIxIiwianRpIjoiMWI0MDZmNjRlMzA1Yzc5Mjk4MmZhODE1OTljNmZmOWFkYjUzOTAwZjAzYTIzYWMwMTdjZjE0YzA0YTgzMzUxMzk0NGNhNWRiYmE5YWIxNzgiLCJpYXQiOjE1NjQwNTU0MDgsIm5iZiI6MTU2NDA1NTQwOCwiZXhwIjoxNTk1Njc3ODA4LCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.CTDMrSCqpEVWMCyFNBSyQbE_QSRvh8CDO0aBId11pBNWG9jozM9xCyaC3Bdb4LLp6VOVdi_8DeKx4HMcdSy6gwAV10gMfOOJOyixReSH9FOHYorJApzFcQS5xaWgFbh8v7RzxL68ImouSISkxr5yvCnixYDS9nKvG4hX1Dy7vOqJ7aFqBM7iPtfXvFO6TnSxnIMDPEYGbElaqdZ25vH5ZuWS0hpYr5hWaFcrjTZ8Um1inL_9AbJXO2RYcV-PY72VNPFAfOy1GTJvI-WQVmdiLKmd35dWvCNky5C5sw4baVwgRrWeY4Tjt8AG6SExnUj-TaeWiu7hzjxXkZzjKLc9Z9yQbtthQvgozfXjEkgc-e8sipVdhkZQC93FjLHRZIBPUKMDVX2NrmjfVBL3FJvjbW2-x6nozXvTQnT4gU1BhB_eZrQhZ4s6cS_UN-9gS3PQLwJmWjY0JlKCKNk2NY4uhWvBnhpJRb2JaLYa7Dk4sIoLwGpiTPc9kp2X4c9WgBfx0BuViL0ZXv3K37j3VQoUcU3fAAXV9RFovb8SGO6oPIuq5XZL-VUbWcDM4PajXpR0bqiaCgmmhw4c0ZR5QpHgrRMQhotpu6SaY3FmQlM2LRwtPzV0IuNxMEcoQhD_i4yEA25ZSq7a25T2jr0lukyH_S1nsVo_rsEIhdZlDlzHSEw");
	pp.subscribe("private-user.7", "192.168.1.168", 81, "broadcasting/auth", "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6Ijk5ODlhN2RlMjljMjcyZjhmM2M0MWNkYTFmM2U3OTU5OGNkODgxZjAxY2ZjZDRjNjk5ZmUyODI4NThmNTNlNjUxMTc3YjExNWQ2ZDQ3OWNhIn0.eyJhdWQiOiIxIiwianRpIjoiOTk4OWE3ZGUyOWMyNzJmOGYzYzQxY2RhMWYzZTc5NTk4Y2Q4ODFmMDFjZmNkNGM2OTlmZTI4Mjg1OGY1M2U2NTExNzdiMTE1ZDZkNDc5Y2EiLCJpYXQiOjE1NjYzNzcxNjgsIm5iZiI6MTU2NjM3NzE2OCwiZXhwIjoxNTk3OTk5NTY4LCJzdWIiOiI3Iiwic2NvcGVzIjpbXX0.BJHc1y5hD15Hfv1N5MxlQv_vq-uELyUxbqF4g5Q7xvzHdCVgLKcDm-0uG6OzWNQe3ZSRzAF1fqzn5wRNurPmG1gO6UltVlpyCTL4F2e48NycDyP_ViIJflKAhK3wUailYAZ-dnbsbgitSvkT0zXaTehQghksbA-XHyDTB2ArjnTVwDbagDBYUaweG8Wjc--lYILHCOAgsZSzuykGLe9vmV97UbO1e397S0LVJZTqoDkRNziUlLsrIEX733CKN-7tFANnbuv9cvny5x6MVnZu-qiaylVVBEBn_JzHqk9TQbnXCmNsWbFNn8DCrs00LAoxuiB-O_jTLgqEIY_LZrBq_7Oalc10o_wUxgPD7GdpZm6hjwXBjZfyUm2jJJKZJGey5uKH_JGHGOGxSCiwQCIT5hGNL994H0VjG_yrm8BL5SeO81rZL-4eEZYe5F27TtxKpwdJQ6dew7GnQ3O1f4CicVMdkMRyRFt5ia_7BBXTmc5yVmOpA64SkpgRK2wHD4jZR5_GP89VFg9f7QXeUXiFzwpr1__t1BzrpHGFg1O6XTH8_mUHhZSwZevSqz8HrNlzNsOBmEi7iRQ1dHxrW5Sfm5xOiTXTbJ3nhDIq3xDNW4xN-_8Ka-MGpPDl6e6IRawDKI8Wct21l3PifR19jctIK0hYS4i4k2ea4oh9yGCFkQc");
	pp.join();
	return WSACleanup();
}
