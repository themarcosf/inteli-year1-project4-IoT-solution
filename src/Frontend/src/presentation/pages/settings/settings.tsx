import React, { useEffect, useState } from 'react'
import './settings.scss'

import {
  Button,
  Form,
  Input,
  Select
} from 'antd'
import { Link, useNavigate, useParams } from 'react-router-dom';

// Tela de configuração de Beacons
const Settings: any = (Parent: any) => {
  const navigate = useNavigate()
  const [beacons, setBeacons] = useState(Parent.props.beacons)

  // Hook para verificar se há mudança nos beacons de acordo com o componente pai
  useEffect(() => {
    // Define os beacons como os beacons definadas no componente pai
    setBeacons(Parent.props.beacons)
  }, [Parent.props.beacons])

  // Função responsável por fazer a requisição que irá editar os Beacons
  async function editBeacons(values: any) {
    await fetch(`http://${import.meta.env.VITE_HOST}:${import.meta.env.VITE_PORT}/api/tags/beacons`, {
      method: "PATCH",
      headers: {
        'Content-Type': 'application/json',
      },
      // Envia para o backend os valores informados no formulário de edição
      body: JSON.stringify(values)
    }).then(() => {
      Parent.props.getBeacons()
    }).then(() => navigate('/')) // Após, navega para a tela Home
  }

  // Ao finalizar o formulário, chama a função de edição de Beacons
  const onFinish: any = (values: any) => {
    if (values) {
      editBeacons(values)
    }
  }

  return (
    <div id="settings">
      <Form
        className='form'
        name="basic"
        labelAlign='left'
        layout="vertical"

        requiredMark={false}
        initialValues={{ remember: true }}
        onFinish={onFinish}
        // onFinishFailed={onFinishFailed}
        autoComplete="off"
      >
        <Form.Item
          label="Posição do Beacon 1"
          name="beacon0"
          rules={[{ required: true, message: 'Preencha com o nome' }]}
          initialValue={0}
        >
          <Input disabled />
        </Form.Item>

        <Form.Item
          label="Distância entre Beacon 1 e 2 (metros)"
          name="beaconX"
          rules={[{ required: true, message: 'Preencha com o nome' }]}
          initialValue={beacons.beaconX | 0}
        >
          <Input type='number' />
        </Form.Item>

        <Form.Item
          label="Distância entre Beacon 1 e 3 (metros)"
          name="beaconY"
          rules={[{ required: true, message: 'Preencha com o nome' }]}
          initialValue={beacons.beaconY | 0}
        >
          <Input type='number' />
        </Form.Item>



        <Form.Item>
          <Button className='button' htmlType="submit">
            Salvar
          </Button>
          <Link to={"/tags"} >
            <Button className='button'>
              Cancelar
            </Button>
          </Link>
        </Form.Item>
      </Form>
    </div>
  )
}

export default Settings