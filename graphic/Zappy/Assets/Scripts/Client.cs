using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Net.Sockets;

public class Client : MonoBehaviour
{
    static private TcpClient client;

    public Client()
    {

    }

    public void ConnectToServer(string ip, int port)
    {
        client = new TcpClient(ip, port);
    }

    public void DisconectFromServer()
    {
        client.Close();
    }
}
