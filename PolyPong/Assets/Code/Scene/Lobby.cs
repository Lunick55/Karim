using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;

public class Lobby : SceneBase<Lobby>
{
    public TMP_InputField ChatMessageBox;
    private ChatLog LobbyChatLog;
    private bool IsGameCountdownRunning;

    private List<int> IncomingServerPlayerIDs = new List<int>();
    private List<int> LocalPlayerIDs = new List<int>();

    public void Start()
    {
        LobbyChatLog = GetComponent<ChatLog>();
        IsGameCountdownRunning = false;

        if (!Persistent.Instance.isServer)
        {
            PlayerData pData = new PlayerData();
            AndrickPlugin.GetPlayerData(ref pData);

            PlayerInfo myPlayer = new PlayerInfo();
            myPlayer.PlayerID = pData.ID;
            myPlayer.Username = AndrickPlugin.GetUsername();
            myPlayer.IsLocallyControlled = true;
            Persistent.Instance.ConnectedPlayers.Add(myPlayer);
        }
    }

    public void Update()
    {
        if (!Persistent.Instance.isServer)
        {
            Debug.Log("YOOO");
            //Get list of all connected users from server.
            int[] playerIDs = new int[AndrickPlugin.GetConnectedUserCount()];
            AndrickPlugin.GetConnectedUserIds(playerIDs);

            IncomingServerPlayerIDs.Clear();
            IncomingServerPlayerIDs.AddRange(playerIDs);

            LocalPlayerIDs.Clear();
            foreach (PlayerInfo Info in Persistent.Instance.ConnectedPlayers)
            {
                LocalPlayerIDs.Add(Info.PlayerID);
            }

            for (int i = 0; i < IncomingServerPlayerIDs.Count; ++i)
            {
                if (!LocalPlayerIDs.Contains(IncomingServerPlayerIDs[i]))
                {
                    PlayerInfo player = new PlayerInfo();
                    player.PlayerID = playerIDs[i];
                    Persistent.Instance.ConnectedPlayers.Add(player);
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
        if (!Persistent.Instance.isServer)
        {
            AndrickPlugin.CreateMessagePacket(string.Format("{0}: {1}", AndrickPlugin.GetUsername(), ChatMessageBox.text));
            ChatMessageBox.text = "";
        }
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
