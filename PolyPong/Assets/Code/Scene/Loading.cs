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
    private const float MAX_WAIT_TIME = 5.0f;

    private bool IsLoading;

    public virtual void Start()
    {
        if (Persistent.Instance.isServer)
            HandleServerCreation();
        else 
            HandleClientConnecting();
    }

    public void HandleClientConnecting()
    {
        if (ClientConnectionCoroutine == null)
        {
            IsLoading = true;
            ClientConnectionCoroutine = StartCoroutine(WaitForClientConnectingResult(Persistent.Instance.ClientInfo));
        }
    }

    IEnumerator WaitForClientConnectingResult(ClientConnectionInfo ClientInfo)
    {
        StartCoroutine(ElipseLoader());
        float WaitCounter = 0.0f;

        if (!AndrickPlugin.ActivateClient(ClientInfo.ipAddress, ClientInfo.username))
        {
            Debug.Log("Failed to successfully activate the client.");
            GetSceneTracker().LoadSceneSynchronously(SceneInfoList.TITLE_MENU);
        }
        else
        {
            while (!AndrickPlugin.DidWeInitiallyConnectToServer())
            {
                if (WaitCounter >= MAX_WAIT_TIME)
                {
                    Debug.Log("Wait time is too long for initial connection.");
                    GetSceneTracker().LoadSceneSynchronously(SceneInfoList.TITLE_MENU);
                    yield return null;
                }

                AndrickPlugin.ProcessPackets();
                AndrickPlugin.ExecuteEvents();
                AndrickPlugin.SendPackets();
                WaitCounter += Time.deltaTime;
                yield return new WaitForEndOfFrame();
            }

            WaitCounter = 0.0f;
            int Result = 0;
            while (AndrickPlugin.DidServerAcceptOurConnection(ref Result) == 0)
            {
                if (WaitCounter >= MAX_WAIT_TIME)
                {
                    Debug.Log("Wait time is too long for server authentification.");
                    GetSceneTracker().LoadSceneSynchronously(SceneInfoList.TITLE_MENU);
                    yield return null;
                }

                AndrickPlugin.ProcessPackets();
                AndrickPlugin.ExecuteEvents();
                AndrickPlugin.SendPackets();
                WaitCounter += Time.deltaTime;
                yield return new WaitForEndOfFrame();
            }

            ClientConnectionCoroutine = null;

            if (Result == 1)
                GetSceneTracker().LoadSceneSynchronously(SceneInfoList.LOBBY);
            else
            {
                GetSceneTracker().LoadSceneSynchronously(SceneInfoList.TITLE_MENU);
            }
        }

        IsLoading = false;
        yield return null;
    }

    public void HandleServerCreation()
    {
        if (ServerCreationCoroutine == null)
        {
          IsLoading = true;
          Debug.Log("LOADING");
          GetSceneTracker().LoadSceneSynchronously(SceneInfoList.SERVER_CONTROL_PANEL);
        }
    }

   //IEnumerator WaitForServerCreationResult(ServerCreationInfo ServerInfo)
   //{
   //    StartCoroutine(ElipseLoader());
   //
   //    //Send the data off to the server and wait for a response.
   //    yield return new WaitForSeconds(5.0f);
   //
   //    ServerCreationCoroutine = null;
   //    GetSceneTracker().LoadSceneSynchronously(SceneInfoList.LOBBY);
   //    IsLoading = false;
   //}

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
