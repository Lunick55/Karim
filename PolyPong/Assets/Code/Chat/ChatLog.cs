using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ChatLog : MonoBehaviour
{
    public int MaxChatsInLog = 50;
    public Transform ParentContentTransform;

    private GameObject ChatItemPrefab = null;
    private LinkedList<ChatItem> ChatItemList;

    public void Start()
    {
        ChatItemPrefab = Resources.Load<GameObject>("Prefab/ChatItem");

        if (ChatItemPrefab)
            Debug.Log("We're in business!");

        ChatItemList = new LinkedList<ChatItem>();
    }

    public void AddChatItem(string Username, string Message)
    {
        if (ChatItemList.Count == MaxChatsInLog)
        {
            LinkedListNode<ChatItem> FirstItem = ChatItemList.First;
            ChatItemList.RemoveFirst();
            Destroy(FirstItem.Value);
        }

        GameObject SpawnedItem = Instantiate(ChatItemPrefab, ParentContentTransform, false);
        ChatItem NewChatItem = SpawnedItem.GetComponent<ChatItem>();
        NewChatItem.PopulateMessage(Username, Message);
        ChatItemList.AddLast(NewChatItem);
    }
}
