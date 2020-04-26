using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;

public class JoinServer : SceneBase<JoinServer>
{
    public TextMeshProUGUI usernameInput;
    public TextMeshProUGUI ipAddress;

    public void OnConnectPressed()
    {
        //Set necessary data that needs to be sent to the server in persistent handler
        //So then we can ask the server about this info in the lobby
        //sceneTracker.LoadSceneSynchronously(SceneInfoList.LOADING_MENU);

        ClientInfo.username = usernameInput.text;
        ClientInfo.ipAddress = ipAddress.text;
        IsServer = false;
        GetSceneTracker().LoadSceneSynchronously(SceneInfoList.LOADING_MENU);
        AndrickPlugin.ActivateClient(ClientInfo.ipAddress, ClientInfo.username);
        //GetSceneTracker().LoadSceneAsync(SceneInfoList.LOADING_MENU, UnityEngine.SceneManagement.LoadSceneMode.Single, OnSceneLoaded);
    }

    //IEnumerator OnSceneLoaded(AsyncOperation loadOperation)
    //{
    //    yield return new WaitUntil(() => loadOperation.isDone == true);
    //
    //    Debug.Log("HELLO?FE<FEBGEJBGFJGB: " + SceneInfoList.CREATE_SERVER.sceneID);
    //    GetSceneTracker().UnloadSceneAsync(SceneInfoList.JOIN_SERVER);
    //}
}