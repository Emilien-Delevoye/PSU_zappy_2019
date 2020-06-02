using UnityEngine;
using TMPro;
using UnityEngine.SceneManagement;

public class ServerJoin : MonoBehaviour
{
    public TMP_InputField IpField;
    public TMP_InputField PortField;

    public Client client;

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
    }

    public void UpdatePort()
    {
        port = PortField.text;
    }

    public void PlayGame()
    {
        client.ConnectToServer(ip, int.Parse(port));
        SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex + 1);
    }
}
