using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class CreateServer : SceneBase<CreateServer>
{
    public TMP_InputField maxUserInput;

    public void OnCreateServer()
    {
        //Set necessary data that needs to be sent to the server in persistent handler
        //So then we can ask the server about this info in the lobby
        int maxUsers = 0;
        if (int.TryParse(maxUserInput.text.ToString(), out maxUsers))
        {
            IsServer = true;
            ServerInfo.maxUsers = maxUserInput.text;
            GetSceneTracker().LoadSceneSynchronously(SceneInfoList.LOADING_MENU);
            AndrickPlugin.ActivateServer(maxUsers);
        }

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
