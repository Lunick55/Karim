using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;

public struct ClientConnectionInfo
{
    public string username;
    public string ipAddress;
}

public struct ServerCreationInfo
{
    public string maxUsers;
}

public class Loading : SceneBase<Loading>
{
    private Coroutine ClientConnectionCoroutine = null;
    private Coroutine ServerCreationCoroutine = null;

    public TextMeshProUGUI ElipseText;

    private const int MAX_ELIPSE = 4;
    private const string ELIPSE = ".";
    private const float TIME_BETWEEN_ELIPSE = 1.0f;

    private bool IsLoading;

    public void Awake()
    {
        if (IsServer)
        {
            HandleServerCreation();
        }
        else 
        {
            HandleClientConnecting();
        }
    }

    public void HandleClientConnecting()
    {
        if (ClientConnectionCoroutine == null)
        {
            IsLoading = true;
            ClientConnectionCoroutine = StartCoroutine(WaitForClientConnectingResult(ClientInfo));
        }
    }

    IEnumerator WaitForClientConnectingResult(ClientConnectionInfo ClientInfo)
    {
        StartCoroutine(ElipseLoader());
        //Send the data off to the server and wait for a response.
        yield return new WaitForSeconds(5.0f);

        ClientConnectionCoroutine = null;
        Debug.Log("LOADING");
        //GetSceneTracker().LoadSceneSynchronously(SceneInfoList.LOBBY_CLIENT);
        IsLoading = false;
    }

    public void HandleServerCreation()
    {
        if (ServerCreationCoroutine == null)
        {
          IsLoading = true;
          Debug.Log("LOADING");
          //GetSceneTracker().LoadSceneSynchronously(SceneInfoList.LOADING_MENU);
          ServerCreationCoroutine = StartCoroutine(WaitForServerCreationResult(ServerInfo));
        }
    }

    IEnumerator WaitForServerCreationResult(ServerCreationInfo ServerInfo)
    {
        StartCoroutine(ElipseLoader());

        //Send the data off to the server and wait for a response.
        yield return new WaitForSeconds(5.0f);

        ServerCreationCoroutine = null;
        GetSceneTracker().LoadSceneSynchronously(SceneInfoList.LOBBY);
        IsLoading = false;
    }

    IEnumerator ElipseLoader()
    {
        float ElipseTimeCounter = 0.0f;

        while (IsLoading)
        {
            ElipseTimeCounter += Time.deltaTime / TIME_BETWEEN_ELIPSE;

            ElipseText.text = "";

            int ElipseCount = Mathf.FloorToInt(ElipseTimeCounter) % MAX_ELIPSE;
            for (int i = 0; i < ElipseCount; ++i)
            {
                ElipseText.text += ELIPSE;
            }

            yield return null;
        }
    }
}
