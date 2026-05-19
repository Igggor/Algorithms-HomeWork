# API Documentation - Task Tracker

## Base URL
```
/api/v1
```

---

## 1. Task Management

### 1.1 Create Task
**Endpoint:** `POST /tasks`
**Status Code:** 201 CREATED
**Description:** Создание новой задачи

**Request Body:**
```json
{
  "name": "string",
  "description": "string",
  "status": "string",
  "priority": "string"
}
```

**Response:**
```json
{
  "id": "uuid",
  "name": "string",
  "description": "string",
  "status": "string",
  "priority": "string"
}
```

---

### 1.2 Get Task by ID
**Endpoint:** `GET /tasks/{id}`
**Status Code:** 200 OK
**Description:** Получение задачи по ID

**Path Parameters:**
- `id` (UUID, required): Уникальный идентификатор задачи

**Response:**
```json
{
  "id": "uuid",
  "name": "string",
  "description": "string",
  "status": "string",
  "priority": "string"
}
```

**Error Responses:**
- 404 Not Found: Задача не найдена

---

### 1.3 Get All Tasks
**Endpoint:** `GET /tasks`
**Status Code:** 200 OK
**Description:** Получение всех задач

**Response:**
```json
[
  {
    "id": "uuid",
    "name": "string",
    "description": "string",
    "status": "string",
    "priority": "string"
  }
]
```

---

### 1.4 Update Task
**Endpoint:** `PUT /tasks/{id}`
**Status Code:** 200 OK
**Description:** Обновление задачи по ID

**Path Parameters:**
- `id` (UUID, required): Уникальный идентификатор задачи

**Request Body:**
```json
{
  "name": "string",
  "description": "string",
  "status": "string",
  "priority": "string"
}
```

**Response:**
```json
{
  "id": "uuid",
  "name": "string",
  "description": "string",
  "status": "string",
  "priority": "string"
}
```

**Error Responses:**
- 404 Not Found: Задача не найдена

---

### 1.5 Move Subtask
**Endpoint:** `PUT /tasks/{taskId}/subtasks/{subtaskId}/move`
**Status Code:** 200 OK
**Description:** Перемещение подзадачи на новую позицию

**Path Parameters:**
- `taskId` (UUID, required): Уникальный идентификатор задачи
- `subtaskId` (UUID, required): Уникальный идентификатор подзадачи

**Query Parameters:**
- `position` (integer, required): Новая позиция подзадачи

**Response:**
```json
{
  "id": "uuid",
  "name": "string",
  "description": "string",
  "status": "string",
  "priority": "string",
  "subtasks": []
}
```

**Error Responses:**
- 404 Not Found: Задача или подзадача не найдена

---

### 1.6 Attach Report to Subtask
**Endpoint:** `PUT /tasks/{taskId}/subtasks/{subtaskId}/report`
**Status Code:** 200 OK
**Description:** Прикрепление отчёта к подзадаче

**Path Parameters:**
- `taskId` (UUID, required): Уникальный идентификатор задачи
- `subtaskId` (UUID, required): Уникальный идентификатор подзадачи

**Request Body:**
```json
{
  "key1": "value1",
  "key2": "value2"
}
```

**Response:**
```json
{
  "id": "uuid",
  "name": "string",
  "description": "string",
  "status": "string",
  "priority": "string",
  "subtasks": []
}
```

**Error Responses:**
- 404 Not Found: Задача или подзадача не найдена

---

### 1.7 Create Subtask from Template
**Endpoint:** `POST /tasks/{taskId}/subtasks/from-template/{templateId}`
**Status Code:** 201 CREATED
**Description:** Создание подзадачи на основе шаблона

**Path Parameters:**
- `taskId` (UUID, required): Уникальный идентификатор задачи
- `templateId` (UUID, required): Уникальный идентификатор шаблона подзадачи

**Query Parameters:**
- `name` (string, optional): Переопределённое имя подзадачи

**Response:**
```json
{
  "id": "uuid",
  "name": "string",
  "description": "string",
  "status": "string",
  "priority": "string",
  "subtasks": []
}
```

**Error Responses:**
- 404 Not Found: Задача или шаблон не найдены

---

## 2. Task Template Management

### 2.1 Create Task Template
**Endpoint:** `POST /task-templates`
**Status Code:** 201 CREATED
**Description:** Создание нового шаблона задачи

**Request Body:**
```json
{
  "name": "string",
  "description": "string",
  "subtasks": []
}
```

**Response:**
```json
{
  "id": "string",
  "name": "string",
  "description": "string",
  "subtasks": []
}
```

---

### 2.2 Get Task Template by ID
**Endpoint:** `GET /task-templates/{id}`
**Status Code:** 200 OK
**Description:** Получение шаблона задачи по ID

**Path Parameters:**
- `id` (string, required): Уникальный идентификатор шаблона

**Response:**
```json
{
  "id": "string",
  "name": "string",
  "description": "string",
  "subtasks": []
}
```

**Error Responses:**
- 404 Not Found: Шаблон не найден

---

### 2.3 Get All Task Templates
**Endpoint:** `GET /task-templates`
**Status Code:** 200 OK
**Description:** Получение всех шаблонов задач

**Response:**
```json
[
  {
    "id": "string",
    "name": "string",
    "description": "string",
    "subtasks": []
  }
]
```

---

## 3. SubTask Template Management

### 3.1 Create SubTask Template
**Endpoint:** `POST /subtask-templates`
**Status Code:** 201 CREATED
**Description:** Создание нового шаблона подзадачи

**Request Body:**
```json
{
  "id": "uuid",
  "name": "string",
  "description": "string",
  "urls": ["string"]
}
```

**Response:**
```json
{
  "id": "uuid",
  "name": "string",
  "description": "string",
  "urls": ["string"]
}
```

---

### 3.2 Get SubTask Template by ID
**Endpoint:** `GET /subtask-templates/{id}`
**Status Code:** 200 OK
**Description:** Получение шаблона подзадачи по ID

**Path Parameters:**
- `id` (UUID, required): Уникальный идентификатор шаблона

**Response:**
```json
{
  "id": "uuid",
  "name": "string",
  "description": "string",
  "urls": ["string"]
}
```

**Error Responses:**
- 404 Not Found: Шаблон подзадачи не найден

---

### 3.3 Get All SubTask Templates
**Endpoint:** `GET /subtask-templates`
**Status Code:** 200 OK
**Description:** Получение всех шаблонов подзадач

**Response:**
```json
[
  {
    "id": "uuid",
    "name": "string",
    "description": "string",
    "urls": ["string"]
  }
]
```

---

### 3.4 Update SubTask Template
**Endpoint:** `PUT /subtask-templates/{id}`
**Status Code:** 200 OK
**Description:** Обновление шаблона подзадачи по ID

**Path Parameters:**
- `id` (UUID, required): Уникальный идентификатор шаблона

**Request Body:**
```json
{
  "name": "string",
  "description": "string",
  "urls": ["string"]
}
```

**Response:**
```json
{
  "id": "uuid",
  "name": "string",
  "description": "string",
  "urls": ["string"]
}
```

**Error Responses:**
- 404 Not Found: Шаблон подзадачи не найден

---

### 3.5 Delete SubTask Template
**Endpoint:** `DELETE /subtask-templates/{id}`
**Status Code:** 204 NO CONTENT
**Description:** Удаление шаблона подзадачи по ID

**Path Parameters:**
- `id` (UUID, required): Уникальный идентификатор шаблона

**Error Responses:**
- 404 Not Found: Шаблон подзадачи не найден

---

## Common HTTP Status Codes

| Status | Description |
|--------|-------------|
| 200 | OK - Успешный запрос |
| 201 | Created - Ресурс успешно создан |
| 204 | No Content - Успешное удаление |
| 400 | Bad Request - Ошибка в запросе |
| 404 | Not Found - Ресурс не найден |
| 500 | Internal Server Error - Ошибка сервера |

---

## Validation

Все поля, помеченные как `@Valid`, подлежат валидации на основе аннотаций Jackson/Jakarta Validation.