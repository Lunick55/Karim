using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class CreateServer : SceneBase<CreateServer>
{
    private const string SERVER_NAME = "Server";

    public TMP_InputField maxUserInput;
    public TMP_InputField portInput;

    public void OnCreateServer()
    {
        int maxUsers;
        if (int.TryParse(maxUserInput.text.ToString(), out maxUsers))
        {
            int port;
            if (int.TryParse(portInput.text.ToString(), out port))
            {
                if (AndrickPlugin.InitServer(SERVER_NAME, port, maxUsers))
                {
                    Persistent.Instance.SetLocalUser(new Server(port, maxUsers));
                    SetScene(SceneInfoList.SERVER_CONTROL_PANEL);
                }
                else
                {
                    SetScene(SceneInfoList.TITLE_MENU);
                }
            }
        }
    }
}
