using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;
using System.Runtime.InteropServices;

[StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
public struct Cummies
{
    //[MarshalAs(UnmanagedType.SysInt, SizeConst = 32)]
    public int numCummies;

    public bool cumFriend;

    public float cumPercent;

    //public string cumName;
};

public class TestScene : MonoBehaviour
{
    // Start is called before the first frame update
    public GameObject testInit = null;
    public GameObject testClientStuff = null;
    public GameObject testServerStuff = null;
    public TextMeshProUGUI counter = null;
    public TextMeshProUGUI console = null;

    int count = 0;

    bool client = false, server = false;

    private Cummies tester;

    void Start()
    {
        count = 0;

        tester = new Cummies();
        tester.numCummies = count;
        tester.cumFriend = true;
        tester.cumPercent = 0.6f;
        //tester.cumName = "Jakob";
    }

    // Update is called once per frame
    void Update()
    {
        counter.text = count.ToString();

        if (client || server)
        {
            Debug.Log("Updatre Network");
            AndrickPlugin.ProcessPackets();
            AndrickPlugin.ExecuteEvents();
            AndrickPlugin.SendPackets();
        }
    }

    public void StartServer()
    {
        if (AndrickPlugin.ActivateServer(5) != 0)
        {
            server = true;
            testInit.SetActive(false);
            testServerStuff.SetActive(true);
            Debug.Log("Server Init Succeeded!");
            console.text = "Server Init Succeeded!";
        }
        else
        {
            Debug.Log("Server Init Failed!");
            console.text = "Server Init Failed!";
        }
    }

    public void StartClient()
    {
        console.text = "Client Init Trying...";
        if (AndrickPlugin.ActivateClient("192.168.1.18", "friend") != 0)
        {
            client = true;
            testInit.SetActive(false);
            testClientStuff.SetActive(true);
            Debug.Log("Client Init Succeeded!");
            console.text = "Client Init Succeeded!";
        }
        else
        {
            Debug.Log("Client Init Failed!");
            console.text = "Client Init Failed!";
        }
    }

    public void Shutdown()
    {
        if (AndrickPlugin.ShutdownNetwork() == 0)
        {
            Debug.Log("Shutdown is a no-go");
        }
        else
        {
            Debug.Log("I've died inside again");
        }
    }

    public void IncrementCounter()
    {
        tester.numCummies = ++count;

        AndrickPlugin.ToDaddy(tester);
        //Debug.Log(AndrickPlugin.FromDaddy().numCummies);
        //SendPacket
    }

    void OnApplicationQuit()
    {
        Shutdown();
    }

}