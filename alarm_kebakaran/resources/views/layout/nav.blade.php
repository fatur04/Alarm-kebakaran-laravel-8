<nav class="navbar navbar-expand-lg navbar-light bg-light">
    <div class="container-fluid">
      <a class="navbar-brand" href="/dashboard">Monitoring</a>
      <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarSupportedContent" aria-controls="navbarSupportedContent" aria-expanded="false" aria-label="Toggle navigation">
        <span class="navbar-toggler-icon"></span>
      </button>
      <div class="collapse navbar-collapse" id="navbarSupportedContent">
        <ul class="navbar-nav me-auto mb-2 mb-lg-0">
          <li class="nav-item">
            <a class="nav-link active" aria-current="page" href="/tabledht">Table Dht11</a>
          </li>
          <li class="nav-item">
            <a class="nav-link" href="/tablemq2">Table Mq2</a>
          </li>
        </ul>
        <form class="d-flex" action="{{ route('logout') }}" method="POST" class="d-none">
          @csrf
          <button type="submit" class="btn btn-danger">Log out</button>
        </form>
      </div>
      <div class="pull-right">

      </div>
    </div>
  </nav>
