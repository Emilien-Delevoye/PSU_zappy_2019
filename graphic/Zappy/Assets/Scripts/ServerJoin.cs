using UnityEngine;
using TMPro;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class ServerJoin : MonoBehaviour
{
    public TMP_InputField IpField;
    public TMP_InputField PortField;

    public GameObject loadingModel;
    public GameObject loadingText;
    public GameObject serverNotFound;

    public Client client;

    private string ip;
    private string port;

    private bool loading = false;

    private float timeToConnect = 5f;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if (loading == true)
        {
            loadingModel.transform.Rotate(0f, 50f * Time.deltaTime, 0f);
            checkIfConnectionEtablished();
        }
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
        timeToConnect = 5f;
        serverNotFound.SetActive(false);
        loadingModel.SetActive(true);
        loadingText.SetActive(true);
        loading = true;
        client.ConnectToServer(ip, int.Parse(port));
    }

    public void checkIfConnectionEtablished()
    {
        if (client.Connected())
        {
            if (client.WaitMessageFromServer() == "WELCOME\n")
            {
                client.SendMessageToServer("GRAPHICAL42\n");
                loading = false;
                loadingModel.SetActive(false);
                loadingText.SetActive(false);
                SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex + 1);
            }
            return;
        }
        timeToConnect -= Time.deltaTime;
        if (timeToConnect <= 0)
        {
            loading = false;
            loadingModel.SetActive(false);
            loadingText.SetActive(false);
            serverNotFound.SetActive(true);
            return;
        }
    }
}
