/*
  Copyright (c) 2012 Vinícius dos Santos Oliveira

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
  */

#ifndef TUFAO_ABSTRACTHTTPSERVERREQUESTHANDLER_H
#define TUFAO_ABSTRACTHTTPSERVERREQUESTHANDLER_H

#include <functional>

#include <QtCore/QObject>
#include <QtCore/QStringList>

#include "tufao_global.h"

namespace Tufao {

class HttpServerRequest;
class HttpServerResponse;

/*!
  This class provides an interface for HttpServerRequest handlers. A request
  handler is usually registered to handle requests matching some set of rules
  and usually used with a set of other handlers.

  A sample request handler is given below:

  \include requesthandler.cpp

  \sa
  HttpServerRequestRouter

  \since
  0.3
  */
class TUFAO_EXPORT AbstractHttpServerRequestHandler: public QObject
{
    Q_OBJECT
public:
    /*!
      Constructs an AbstractHttpServerRequestHandler object.
      */
    explicit AbstractHttpServerRequestHandler(QObject *parent = 0);

    /*!
      Implicit conversion operator to std::function functor object.

      \warning
      You shall not use the returned object after the AbstractHttpServerRequest
      object is destroyed.

      \since
      1.0
     */
    operator std::function<bool(HttpServerRequest&, HttpServerResponse&)>();

public slots:
    /*!
      Handles the \p request using the \p response object.

      \retval true
      If the handler has responded to the request.

      \retval false
      If the requested page can't be generated by this handler. The connection
      should remain open and the \p response object shouldn't be used, leaving
      the response free to be used by other handlers in the chain.

      \since
      1.0
      */
    virtual bool handleRequest(Tufao::HttpServerRequest &request,
                               Tufao::HttpServerResponse &response) = 0;
};

inline AbstractHttpServerRequestHandler::operator
std::function<bool(HttpServerRequest&, HttpServerResponse&)>()
{
    return [this](HttpServerRequest &req, HttpServerResponse &res) {
        return this->handleRequest(req, res);
    };
}

} // namespace Tufao

#endif // TUFAO_ABSTRACTHTTPREQUESTHANDLER_H
