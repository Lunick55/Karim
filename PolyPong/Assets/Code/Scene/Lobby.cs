using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;

public class Lobby : SceneBase<Lobby>
{
    public TMP_InputField ChatMessageBox;
    private ChatLog LobbyChatLog;
    private bool IsGameCountdownRunning;

    public void Start()
    {
        LobbyChatLog = GetComponent<ChatLog>();
        IsGameCountdownRunning = false;

        if (!Instance.GetPersistentInstance().isServer)
        {
            PlayerData pData = new PlayerData();
            AndrickPlugin.GetPlayerData(ref pData);

            Player myPlayer = new Player();
            myPlayer.PlayerID = pData.ID;
            myPlayer.name = AndrickPlugin.GetUsername();

            Instance.GetPersistentInstance().ConnectedPlayers.Add(myPlayer);
        }
    }

    public void Update()
    {
        if (!Instance.GetPersistentInstance().isServer)
        {
            int[] playerIDs = new int[AndrickPlugin.GetConnectedUserCount()];
            AndrickPlugin.GetConnectedUserId(playerIDs);

            for (int i = 0; i < playerIDs.Length; i++)
            {
                if (Instance.GetPersistentInstance().ConnectedPlayers[i].PlayerID != playerIDs[i])
                {
                    Player player = new Player();
                    player.PlayerID = playerIDs[i];

                    Instance.GetPersistentInstance().ConnectedPlayers.Add(player);
                }
            }
        }

        if (Input.GetKeyDown(KeyCode.Return))
            OnSendClicked();

        AndrickPlugin.ProcessPackets();
        AndrickPlugin.ExecuteEvents();

        //
        string tempLog = AndrickPlugin.ReadMessageLog();
        while(tempLog != null)
        {
            LobbyChatLog.AddChatItem(tempLog);
            tempLog = AndrickPlugin.ReadMessageLog();
        }

        //tempLog = AndrickPlugin.FromDaddy(tempLog);

        AndrickPlugin.SendPackets();
    }

    public void OnSendClicked()
    {
        AndrickPlugin.CreateMessagePacket(string.Format("{0}: {1}", AndrickPlugin.GetUsername(), ChatMessageBox.text));
        ChatMessageBox.text = "";
    }

    public void OnStartGameClicked()
    {
        if (!IsGameCountdownRunning)
            StartCoroutine(StartGameCountdown());
    }

    private IEnumerator StartGameCountdown()
    {
        if (IsGameCountdownRunning)
        {
            Debug.LogWarning("Already counting down!");
            yield return null;
        }
        else
        {
            IsGameCountdownRunning = true;

            int MaxCount = 3;
            int StartCounter = 0;

            while (StartCounter < MaxCount)
            {
                LobbyChatLog.AddChatItem(string.Format("Server: Starting game in {0}!", MaxCount - StartCounter));
                yield return new WaitForSeconds(0.7f);
                ++StartCounter;
            }

            IsGameCountdownRunning = false;
            StartGame();

        }
    }

    private void StartGame()
    {
        Debug.Log("This is when we'd call into the DLL to start the game.");
        LobbyChatLog.AddChatItem("Server: This is when we'd call into the DLL to start the game.");
    }
}
