#include "Common.h"
#include "Client.h"
using namespace std;
int main()
{
    char input = 'A';
    Client client;
    client.Init();
    int client_sockfd;
    client_sockfd = client.GetSockfd();
    while(1)
    {
        cout << "enter input char :";
        cin >> input;

        write(client_sockfd, &input, 1);
        read(client_sockfd, &input, 1);
        cout << "server response:" << input << endl;
    }

    close(client_sockfd);
}

