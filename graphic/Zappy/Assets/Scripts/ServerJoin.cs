using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Net;
using System.Net.Sockets;
using UnityEngine.Networking;
using UnityEngine.UI;
using TMPro;

public class ServerJoin : MonoBehaviour
{

    public TMP_InputField IpField;
    public TMP_InputField PortField;

    private string ip;
    private string port;

    // Start is called before the first frame update
    void Start()
    {
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void UpdateIp()
    {
        ip = IpField.text;

        Debug.Log(ip);
    }

    public void UpdatePort()
    {
        port = PortField.text;

        Debug.Log(port);
    }
}
