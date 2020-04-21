using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class CreateServer : SceneBase<CreateServer>
{
    public TextMeshProUGUI usernameInput;
    public TextMeshProUGUI maxUserInput;

    public void OnCreateServer()
    {
        //Set necessary data that needs to be sent to the server in persistent handler
        //So then we can ask the server about this info in the lobby
        ServerInfo.username = usernameInput.text;
        ServerInfo.maxUsers = maxUserInput.text;
        IsServer = true;
        GetSceneTracker().LoadSceneSynchronously(SceneInfoList.LOADING_MENU);
        //GetSceneTracker().LoadSceneAsync(SceneInfoList.LOADING_MENU, UnityEngine.SceneManagement.LoadSceneMode.Single, OnSceneLoaded);
    }

    //IEnumerator OnSceneLoaded(AsyncOperation loadOperation)
    //{
    //    yield return new WaitUntil(() => loadOperation.isDone == true);
    //
    //
    //    Debug.Log("HELLO?FE<FEBGEJBGFJGB: " + SceneInfoList.CREATE_SERVER.sceneID);
    //    GetSceneTracker().UnloadSceneAsync(SceneInfoList.CREATE_SERVER);
    //}
}
