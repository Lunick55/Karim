using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;

public class TestScene : MonoBehaviour
{
    // Start is called before the first frame update
    public GameObject testInit = null;
    public GameObject testClientStuff = null;
    public GameObject testServerStuff = null;
    public TextMeshProUGUI counter = null;

    int count = 0;

    bool client = false, server = false;

    void Start()
    {
        count = 0;
    }

    // Update is called once per frame
    void Update()
    {
        counter.text = count.ToString();

        if(client)
        {
            AndrickPlugin.UpdateClient();
        }
        else if(server)
        {
            AndrickPlugin.UpdateServer();
        }

    }

    public void StartServer()
    {
        if(AndrickPlugin.ActivateServer(5) != 0)
        {
            server = true;
            testInit.SetActive(false);
            testServerStuff.SetActive(true);
            Debug.Log("Server Init Succeeded!");
        }
        else
        {
            Debug.Log("Server Init Failed!");
        }
    }

    public void StartClient()
    {
        if(AndrickPlugin.ActivateClient("192.168.1.18") != 0)
        {
            client = true;
            testInit.SetActive(false);
            testClientStuff.SetActive(true);
            Debug.Log("Client Init Succeeded!");
        }
        else
        {
            Debug.Log("Client Init Failed!");
        }
    }

    public void IncrementCounter()
    {
        count++;
    }
}
