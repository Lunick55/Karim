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
        ClientInfo.username = usernameInput.text;
        ClientInfo.ipAddress = ipAddress.text;
        Persistent.Instance.isServer = false;
        GetSceneTracker().LoadSceneSynchronously(SceneInfoList.LOADING_MENU);
    }
}