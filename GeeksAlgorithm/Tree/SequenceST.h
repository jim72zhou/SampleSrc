#ifndef GEEKS_SEQUENCE_ST_H
#define GEEKS_SEQUENCE_ST_H

#include <iostream>
#include <cassert>

using namespace std;

template<typename Key, typename Value>
class SequenceST
{
private:
    struct SeqNode
	{
        Key key;
        Value value;
        SeqNode *next;

        SeqNode(Key key, Value value)
		{
            this->key = key;
            this->value = value;
            this->next = nullptr;
        }
    };

    SeqNode* m_head;
    int m_count;

public:
    SequenceST()
	{
        m_head = nullptr;
        m_count = 0;
    }

    ~SequenceST()
	{
        while(m_head != nullptr)
		{
            SeqNode *node = m_head;
            m_head = m_head->next;
            delete node;
            --m_count;
        }

        assert(m_head == nullptr && m_count == 0);
    }

    int size()
	{
        return m_count;
    }

    bool isEmpty()
	{
        return m_count == 0;
    }

    void insert(Key key, Value value)
	{
        SeqNode *node = m_head;
        while(node != nullptr)
		{
            if(key == node->key)
			{
                node->value = value;
                return;
            }
            node = node->next;
        }

        SeqNode *newNode = new SeqNode(key, value);
        newNode->next = m_head;
        m_head = newNode;
        ++m_count;
    }

    bool contain(Key key)
	{
        SeqNode *node = m_head;
        while(node != nullptr)
		{
            if(key == node->key)
			{
                return true;
            }
            node = node->next;
        }

        return false;
    }

    Value* search(Key key)
	{
        SeqNode *node = m_head;
        while(node != nullptr)
		{
            if(key == node->key)
			{
                return &(node->value);
            }
            node = node->next;
        }

        return nullptr;
    }

    void remove(Key key)
	{
        if(key == m_head->key)
		{
            SeqNode* delNode = m_head;
            m_head = m_head->next;
            delete delNode;
            --m_count;
            return;
        }

        SeqNode *node = m_head;
        while(node->next != nullptr && node->next->key != key)
            node = node->next;

        if(node->next != nullptr)
		{
            SeqNode* delNode = node->next;
            node->next = delNode->next;
            delete delNode;
            --m_count;
            return;
        }
    }
};

#endif //GEEKS_SEQUENCE_ST_H
