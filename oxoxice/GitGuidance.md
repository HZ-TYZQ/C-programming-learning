written by ChatGPT

# oxoxice的 Git 上手练习

oxoxice，你的 Windows 电脑已经装好 Git，Git 和 gh 的认证也已完成，直接练习就行。

**平时照常在文件资源管理器（Explorer）里找文件、双击打开、编辑保存。需要记录或上传修改时，再打开终端输入 Git 命令。** VS Code 和 C 语言以后再学。

## 场景一：准备好项目文件夹

如果电脑上已经有克隆好的 `C-programming-learning` 文件夹，直接打开它，跳过下载。

如果还没有：在资源管理器里选一个存放学习资料的文件夹，在空白处右键 →“在终端中打开”，输入下面这行并按回车：

```powershell
git clone https://github.com/HZ-TYZQ/C-programming-learning.git
```

下载完成后，在资源管理器里双击进入新出现的 `C-programming-learning` 文件夹。

**之后都在这一层空白处右键打开终端**：这里能同时看到 `oxoxice`、`TYZQ`、`Collaboration` 三个文件夹。如果终端开错位置，关掉后在正确文件夹重新打开就好。

命令一次输入一行，按回车执行。出现报错先停下，不要继续输入后面的命令。项目只需克隆一次，以后通过 `git pull` 更新。

## 场景二：我要开始写第一份笔记

先在项目文件夹打开终端，检查状态：

```powershell
git status
```

看到 `working tree clean` 表示没有未提交的修改，再逐行执行：

```powershell
git switch main
git pull --ff-only
git switch -c oxoxice/first-note
```

- `switch main`：切换到主分支，也就是大家汇总成果的地方。
- `pull --ff-only`：获取远程更新并更新当前分支；如果本地和远程各自有不同提交，就停下来，让 HZ-TYZQ 帮忙检查。
- `switch -c ...`：创建并切换到自己的分支，先在这里修改，之后再合入 `main`。分支名中的 `/` 不会创建文件夹。

想确认自己在哪个分支，输入：

```powershell
git branch
```

它会列出本地分支，带 `*` 的就是当前分支，此时应该是 `oxoxice/first-note`。

现在回到资源管理器，进入 `oxoxice` 文件夹，右键新建一个文本文档，命名为 `note.txt`。可以在“查看”菜单里打开“文件扩展名”，避免变成 `note.txt.txt`。

双击文件，用记事本写一句“今天开始学习 Git”，按 `Ctrl + S` 保存。然后回到刚才在**项目最外层**打开的终端。

## 场景三：笔记写好了，我要记录并上传

先看看 Git 有没有发现新文件：

```powershell
git status
```

看到 `Untracked files` 下有 `oxoxice/note.txt`，说明新文件还没加入 Git 的记录。依次执行：

```powershell
git add oxoxice/note.txt
git diff --staged
git commit -m "添加第一份学习笔记"
git push -u origin oxoxice/first-note
```

这四步分别是：

1. **add**：选中这个文件的当前修改，放入“暂存区”，准备提交。
2. **diff --staged**：检查选中的内容。`+` 表示新增，`-` 表示删除；如果停在查看界面，按英文 `q` 退出。
3. **commit**：在电脑上记下一次修改。引号里写清楚改了什么，可以用中文。
4. **push**：把提交上传到 GitHub。`origin` 是远程仓库的简称；新分支第一次加 `-u`，记住对应关系。

**保存文件 ≠ 提交 ≠ 上传。** 只有保存，对方看不到；只有 commit，也还在你电脑上。

打开 [仓库网页](https://github.com/HZ-TYZQ/C-programming-learning)，把分支选择器从 `main` 改成 `oxoxice/first-note`，就能在 `oxoxice` 文件夹里看到笔记。此时 `main` 还没有它，是正常的。

## 场景四：我又给这份笔记加了一句话

继续在刚才的分支上操作：双击 `note.txt`，补一句话，保存，然后回到终端：

```powershell
git status
git diff
git add oxoxice/note.txt
git diff --staged
git commit -m "补充今天学会的 Git 命令"
git push
```

`git diff` 查看已跟踪文件中还没暂存的修改；`git diff --staged` 查看准备提交的修改。新文件在 add 之前不会显示在普通 `git diff` 里。

这次只需 `git push`，因为上次已经用 `-u` 记住了对应关系。每次修改都要重新 add；如果 add 后又编辑了文件，也要再次 add 才能包含后面的修改。

## 场景五：我选错文件了，或者想撤销修改

**情况 A：刚才执行了 add，但暂时不想提交这个文件。**

```powershell
git restore --staged oxoxice/note.txt
git status
```

这会取消选中，文件里的文字还在。想提交时重新 add 就行。

**情况 B：这份笔记已经提交过，现在又改乱了，想放弃刚才的修改。**

优先在记事本里按 `Ctrl + Z` 撤销。如果确实要丢掉修改、恢复文件，先检查 `git status`；如果已经 add，先按情况 A 取消暂存，再执行：

```powershell
git restore oxoxice/note.txt
```

**这条命令会丢掉这个文件尚未提交的修改。** 在已取消暂存的前提下，它会恢复为最近一次提交的内容；记事本里如果还开着旧内容，关闭后重新打开，别把旧内容再次保存回去。

记住区别：**带 `--staged` 是取消选中，不带它是覆盖文件内容。** 尚未 add 的新文件不能靠 restore 恢复。已经提交的内容写错了，就正常修改后再提交一次修正，不用强行重写历史。

## 场景六：笔记写完了，想让 HZ-TYZQ 合进主分支

推送只是上传自己的分支。要把内容合进 `main`，在 GitHub 上发起 **PR（Pull Request，合并请求）**：

1. 打开仓库网页 → `Pull requests` → `New pull request`。
2. 选择 **base: `main`**、**compare: `oxoxice/first-note`**，表示把自己的修改合入主分支。
3. 检查文件变化，点击 `Create pull request`，写明这次新增了什么，提交后把链接发给 HZ-TYZQ。
4. 如果对方建议修改，PR 合并前继续按场景四修改、提交、推送，原 PR 会自动更新。

等 PR 显示 **Merged**，确认本地修改都已提交、推送，`git status` 显示 `working tree clean`，再执行：

```powershell
git switch main
git pull --ff-only
```

网页合并不会自动更新电脑，所以要 pull 一次。下一件事从更新后的 `main` 新建分支，比如 `git switch -c oxoxice/second-note`，不要继续用已合并的旧分支。

如果只是继续昨天没写完的任务，不用再建分支。用 `git branch` 查看；需要切回已有分支时，在工作区干净的情况下用 `git switch oxoxice/first-note`，这时不加 `-c`。

## 先熟练掌握这些就够了

| 想做什么 | 用什么 |
| --- | --- |
| 不知道当前是什么情况 | `git status` |
| 看自己在哪个分支 | `git branch` |
| 开新分支 / 切回已有分支 | `git switch -c 分支名` / `git switch 分支名` |
| 获取当前分支的远程更新 | `git pull --ff-only` |
| 看修改 / 看准备提交的修改 | `git diff` / `git diff --staged` |
| 选中一个文件的修改 | `git add 文件路径` |
| 记下一次修改 | `git commit -m "这次改了什么"` |
| 上传提交 | 首次 `git push -u origin 分支名`，之后 `git push` |
| 取消选中，保留文字 | `git restore --staged 文件路径` |
| 放弃文件的未暂存修改 | `git restore 文件路径`，执行前确认不要这些内容了 |

表里的“分支名”“文件路径”要换成真实内容，不要原样输入。先明确选文件，不急着用 `git add .` 一次添加所有修改。

遇到报错，把**刚才输入的命令、完整报错、`git status` 的结果**发给 HZ-TYZQ。找不到仓库时先检查终端是否在项目文件夹；认证或权限报错让他检查已有配置。不要靠删除项目或强制推送来“重试”。
