using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;

public class Lobby : SceneBase<Lobby>
{
    public TMP_InputField ChatMessageBox;
    private ChatLog LobbyChatLog;
    private bool IsGameStarting;

    public void Start()
    {
        LobbyChatLog = GetComponent<ChatLog>();
        IsGameStarting = false;
    }

    public void Update()
    {
        if (Input.GetKeyDown(KeyCode.Return))
            OnSendClicked();
    }

    public void OnSendClicked()
    {
        LobbyChatLog.AddChatItem("NOOB", ChatMessageBox.text);
        ChatMessageBox.text = "";
    }

    public void OnStartGameClicked()
    {
        if (!IsGameStarting)
        {
            StartCoroutine(StartGame());
        }
    }

    private IEnumerator StartGame()
    {
        if (IsGameStarting)
        {
            Debug.LogWarning("Already counting down!");
            yield return null;
        }
        else
        {
            IsGameStarting = true;

            int MaxCount = 3;
            int StartCounter = 0;

            while (StartCounter <= MaxCount)
            {
                LobbyChatLog.AddChatItem("Server", string.Format("Starting game in {0}!", MaxCount - StartCounter));
                yield return new WaitForSeconds(1.0f);
            }

            IsGameStarting = false;
        }
    }
}
