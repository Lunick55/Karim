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
        Persistent.Instance.ClientInfo.username = usernameInput.text;
        Persistent.Instance.ClientInfo.ipAddress = ipAddress.text;
        GetSceneTracker().LoadSceneSynchronously(SceneInfoList.LOADING_MENU);
    }
}