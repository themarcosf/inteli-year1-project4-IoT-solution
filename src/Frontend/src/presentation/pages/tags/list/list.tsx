import React, { useState, useEffect } from 'react'
import { Space, Table, Button, Popover, Modal, message } from 'antd'
import type { ColumnsType } from 'antd/es/table'
import { Link, useNavigate } from 'react-router-dom'

import './list.scss'

import VisibilityIcon from '@mui/icons-material/Visibility'
import EditIcon from '@mui/icons-material/Edit'
import DeleteIcon from '@mui/icons-material/Delete'
import InfoIcon from '@mui/icons-material/Info'
import { ExclamationCircleFilled } from '@ant-design/icons';


// Define a tipagem de uma Tag
type TagType = {
  _id: number;
  macAddress: string;
  name: string;
  category: string;
  battery: any;
  isMoving: boolean
  position: [number, number]
}

// Define o modal de confirmação de exclusão
const { confirm } = Modal;

// Tela de listagem de Tags
const List: any = (Parent: any) => {
  const navigate = useNavigate()
  // Função para definir uma tag como ativa ao clicar em visualizá-la na tela
  // Navegará para a tela de localização, destacando a tag selecionada
  const handleActive: Function = (index: number) => {
    Parent.props.changeTag(index)
    Parent.props.changePage(0)
  }

  // Define as tags e as novas tags de acordo com o componente pai
  const [tags, setTags] = useState(Parent.props.tags)
  const [newTags, setNewTags] = useState(Parent.props.newTags)

  // Hook para definir as tags de acordo com os dados do componente pai sempre que houver uma mudança
  useEffect(() => {
    let messageText = localStorage.getItem("message")
    if (messageText) {
      message.success(messageText, 3);
      localStorage.removeItem("message")
    }

    setTags(Parent.props.tags)
  }, [Parent.props.tags])

  // Hook para verificar se há alguma mudança nas tags não cadastradas de acordo com o componente pai 
  useEffect(() => {
    // Define as novas tags como as recebecidas pelo componente pai
    setNewTags(Parent.props.newTags)
  }, [Parent.props.newTags])

  // Função responsável por fazer a requisição de deletação de Tag, passando como parâmetro o ID da Tag 
  async function deleteTag(id: string) {
    await fetch(`http://${import.meta.env.VITE_HOST}:${import.meta.env.VITE_PORT}/api/tags/${id}`, {
      method: "DELETE",
      headers: {
        'Content-Type': 'application/json'
      }
    }).then(() => {
      localStorage.setItem("message", "Tag deletada com sucesso!")
      Parent.props.getTags()
    }).then(() => navigate('/tags')) // Após,navega novamente para listagem de tags para atualizar a tela
  }

  // Função que renderiza o modal de confirmação de exclusão de tags
  const showConfirm: Function = (id: string) => {
    confirm({
      title: 'Você realmente desaja excluir a Tag?',
      icon: <ExclamationCircleFilled />,
      // content: 'Não poderá ser desfeita',
      okText: "Excluir",
      okType: 'danger',
      cancelText: 'Não',
      onOk() {
        deleteTag(id)
      },
      onCancel() {
        console.log('Cancel');
      },
    });
  };

  // Constrói a estrutura da tabela de Tags
  const columns: ColumnsType<TagType> = [
    {
      title: 'Tag',
      dataIndex: 'name',
      key: 'name',
    },
    {
      title: 'Categoria',
      dataIndex: 'category',
      key: 'category',
    },
    {
      title: 'Ações',
      key: 'action',
      render: (_, obj, index) => (
        <Space size="middle">
          <Link onClick={() => handleActive(index)} to={"/"}>
            <VisibilityIcon className='actionIcon' />
          </Link>
          <Link
            to={`/tags/edit/${obj._id}`}
            state={{ name: obj.name, macAddress: obj.macAddress, category: obj.category }}
          >
            <EditIcon className='actionIcon' />
          </Link>
          <DeleteIcon onClick={() => showConfirm(obj._id)} className='actionIcon' />
        </Space>
      )
    }
  ]

  const content: any = (
    <div>Clique em Adicionar Tag</div>
  )

  // Função que exibirá uma notificação na tela que há novas tags caso ela não tenha sido cadastrada ainda
  const haveNewTags: Function = () => {
    if (newTags.length > 0) {
      return (
        <Popover placement='bottom' content={content} title="Novas tags encontradas" trigger="click">
          <InfoIcon className='icon' />
        </Popover>
      )
    }
  }

  return (
    <div id="tags-list">
      <Table rowKey="name" className='table' columns={columns} dataSource={tags} pagination={{ pageSize: 5 }} />
    </div>
  )
}

export default List